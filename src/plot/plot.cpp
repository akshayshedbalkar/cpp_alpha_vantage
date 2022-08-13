#include <stdio.h>   // for remove, size_t
#include <algorithm> // for count, find, remove
#include <iostream>  // for operator<<, basic_ostream, basic_ostre...
#include <iterator>  // for next
#include <string>    // for string, char_traits, basic_string, all...

#include "gnuplot-iostream.h" // for Gnuplot
#include "plot.h"

enum class Plot_type
{
  PLOT = 0,
  REPLOT = 1
};

int Plot::csv_column{ 0 };
float Plot::time_in_weeks{ 0.0 };
std::string Plot::csv_column_name{ "" };

Plot::Plot() {}

Plot::Plot(std::string s, float time)
{
  csv_column_name = s;
  time_in_weeks = time;
}

float
Plot::get_time_in_weeks()
{
  return time_in_weeks;
}

void
Plot::process_data(std::string &s) const
{
  std::string test{ "Thank" };
  if (s.find(test) != std::string::npos)
  {
    throw "Too many or too frequent API calls. Wait a bit and try again.\n";
  }

  size_t pos = s.find(csv_column_name);
  auto s_end = std::next(s.begin(), pos);
  csv_column = static_cast<int>(std::count(s.begin(), s_end, ',')) + 1;

  s.insert(0, "#");
  s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
}

void
Plot::create_temp_file(std::string const &data, std::string const &file_name)
{
  std::ofstream out(file_name.c_str());
  out << data;
  out.close();
  if (std::find(file_names.begin(), file_names.end(), file_name) ==
      file_names.end())
  {
    file_names.push_back(file_name);
  }
}

void
Plot::setup_gnuplot(Gnuplot &g) const
{
  g << "set datafile separator ','\n";
  g << "set xdata time\n";
  g << "set timefmt \"%Y-%m-%d\"\n";
  g << "set format x \"%d/%m/%y\"\n";
  g << "set ylabel \"%\"\n";
  g << "set title \"" << function.c_str() << "\" noenhanced\n";
  g << "set terminal qt size 1600,1000\n";
  g << "set grid\n";
}

void
Plot::get_first_datapoint(Gnuplot &g, std::string const &file_name) const
{
  constexpr int days_in_a_week{ 6 };
  g << " system(\"awk -i inplace 'NR<="
    << static_cast<int>(days_in_a_week * time_in_weeks) << "' "
    << file_name.c_str() << "\")\n";
  g << " first_" << file_name.c_str() << "=system(\"awk -F',' 'END {print $"
    << csv_column << "}' " << file_name.c_str() << "\")\n";
}

void
Plot::percentage_plot(Gnuplot &g,
                      std::string const &file_name,
                      const Plot_type type) const
{
  get_first_datapoint(g, file_name);

  std::string p;
  if (type == Plot_type::PLOT)
  {
    p = "plot";
  }
  else if (type == Plot_type::REPLOT)
  {
    p = "replot";
  }

  g << p.c_str() << " \"" << file_name.c_str() << "\" using 1:(($" << csv_column
    << "-first_" << file_name.c_str() << ")*100/first_" << file_name.c_str()
    << ") with lines title \"" << file_name.c_str() << "\"\n";
}

void
Plot::display(std::string const &file_name) const
{
  Gnuplot temp;
  setup_gnuplot(temp);

  percentage_plot(temp, file_name, Plot_type::PLOT);
}

void
Plot::display() const
{
  Gnuplot temp;
  setup_gnuplot(temp);
  int i{ 0 };

  for (auto const &file : file_names)
  {
    if (i == 0)
    {
      percentage_plot(temp, file, Plot_type::PLOT);
    }
    else
    {
      percentage_plot(temp, file, Plot_type::REPLOT);
    }
    i++;
  }
}

void
Plot::cleanup() const
{
  for (auto const &i : file_names)
  {
    remove(i.c_str());
  }
}

void
Plot::set_function(std::string const &function)
{
  this->function = function;
}

Plot::~Plot()
{
  cleanup();
}
