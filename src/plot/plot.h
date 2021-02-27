#ifndef PLOT_H
#define PLOT_H

#include <string>

#include "gnuplot-iostream.h"

enum class Plot_type;

class Plot {
    private:
        std::vector<std::string> file_names;

    public:
        void process_data(std::string &s);
        void display();

        void display_stock_data(const std::string &s);
        void create_temp_file(const std::string &data, const std::string &file_name);
        void setup_gnuplot();
        void get_first_datapoint(Gnuplot &g, const std::string &file_name);
        void percentage_plot(Gnuplot &g, const std::string &file_name, Plot_type type);
        void cleanup();
        void setup_gnuplot(Gnuplot &g);

        ~Plot();
};

#endif /* ifndef PLOT_H */
