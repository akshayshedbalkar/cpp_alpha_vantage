#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <numeric>

#include "gnuplot-iostream.h"
#include "plot.h"

enum class Plot_type{
    PLOT=0,
    REPLOT=1
};

void Plot::process_data(std::string &s) {
    s.insert(0, "#");
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
}

void Plot::create_temp_file(const std::string &data, const std::string &file_name) {
    std::ofstream out(file_name.c_str());
    out << data;
    out.close();
    file_names.push_back(file_name);
}

void Plot::setup_gnuplot(Gnuplot &g) {
    g << "set datafile separator ','\n";
    g << "set xdata time\n";
    g << "set timefmt \"%Y-%m-%d\"\n";
    g << "set format x \"%m/%Y\"\n";
    g << "set ylabel \"%\"\n";
}

void Plot::get_first_datapoint(Gnuplot &g, const std::string &file_name){
    g << " first_"<<file_name.c_str()<<"=system(\"awk -F',' 'END {print $2}' " << file_name.c_str() <<"\")\n";
}

void Plot::percentage_plot(Gnuplot &g, const std::string &file_name, Plot_type type){
    std::string p;
    if(type == Plot_type::PLOT){
        p="plot";
    }else if(type == Plot_type::REPLOT){
        p="replot";
    }

    g << p.c_str()<< " \"" << file_name.c_str() << "\" using 1:(($2-first_"<<file_name.c_str()<<")*100/first_"<<file_name.c_str()<<") with lines title \"" << file_name.c_str() << "\"\n";
}

void Plot::display_stock_data(const std::string &file_name) {
    Gnuplot temp;
    setup_gnuplot(temp);

    get_first_datapoint(temp,file_name);
    percentage_plot(temp,file_name,Plot_type::PLOT);

}

void Plot::display() {
    Gnuplot temp;
    setup_gnuplot(temp);
    int i=0;

    for(const auto& file : file_names) {
        get_first_datapoint(temp,file);
        if(i==0){
            percentage_plot(temp, file, Plot_type::PLOT);
        }else{
            percentage_plot(temp, file, Plot_type::REPLOT);
        }
        i++;
    }

}

void Plot::cleanup() {
    for(const auto& i : file_names) {
        remove(i.c_str());
    }
}

Plot::~Plot() {
    cleanup();
}
