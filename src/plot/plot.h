#ifndef PLOT_H
#define PLOT_H

#include <string> // for string
#include <vector> // for vector

#include "gnuplot-iostream.h" // for Gnuplot

enum class Plot_type;

class Plot
{
private:
  std::vector<std::string> file_names;
  std::string function;
  static std::string csv_column_name;
  static int csv_column;
  static float time_in_weeks;

public:
  Plot();
  Plot(std::string s, float time);

  static float get_time_in_weeks();

  void display() const;
  void display(std::string const &s) const;

  void setup_gnuplot(Gnuplot &g) const;
  void process_data(std::string &s) const;
  void get_first_datapoint(Gnuplot &g, std::string const &file_name) const;
  void percentage_plot(Gnuplot &g,
                       std::string const &file_name,
                       const Plot_type type) const;
  void set_function(std::string const &function);

  void create_temp_file(std::string const &data, std::string const &file_name);
  void cleanup() const;

  ~Plot();
};

#endif /* ifndef PLOT_H */
