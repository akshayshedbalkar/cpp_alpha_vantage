#ifndef PLOT_H
#define PLOT_H value

#include <string>

#include "gnuplot-iostream.h"

class Plot {
   private:
    Gnuplot gp;
    std::string file_names;

   public:
    void process_data(std::string &s);
    void display();

    void display_stock_data(const std::string &s);
    void create_temp_file(const std::string &data, const std::string &file_name);
    void setup_gnuplot();
    void cleanup();
    void setup_gnuplot(Gnuplot &g);

    ~Plot();
};

#endif /* ifndef PLOT_H */
