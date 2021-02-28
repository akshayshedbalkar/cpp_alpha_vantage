#ifndef PLOT_H
#define PLOT_H

#include <string>

#include "gnuplot-iostream.h"

enum class Plot_type;

class Plot
{
  private:
    std::vector<std::string> file_names;

  public:
    void display() const;
    void display(const std::string &s) const;

    void setup_gnuplot(Gnuplot &g) const;
    void process_data(std::string &s) const;
    void get_first_datapoint(Gnuplot &g, const std::string &file_name) const;
    void percentage_plot(Gnuplot &g, const std::string &file_name, const Plot_type type) const;

    void create_temp_file(const std::string &data, const std::string &file_name);
    void cleanup() const;

    ~Plot();
};

#endif /* ifndef PLOT_H */
