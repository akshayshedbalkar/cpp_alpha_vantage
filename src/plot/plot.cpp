#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

#include "gnuplot-iostream.h"
#include "plot.h"

void Plot::process_data(std::string &s) {
    s.insert(0, "#");
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
}

void Plot::create_temp_file(const std::string &data, const std::string &file_name) {
    std::ofstream out(file_name.c_str());
    out << data;
    out.close();
    file_names.append(" ");
    file_names.append(file_name);
}

void Plot::setup_gnuplot(Gnuplot &g) {
    g << "set datafile separator ','\n";
    g << "set xdata time\n";
    g << "set timefmt \"%Y-%m-%d\"\n";
    g << "set format x \"%m/%Y\"\n";
}

void Plot::display_stock_data(const std::string &file_name) {
    Gnuplot temp;
    setup_gnuplot(temp);
    temp << "set ylabel \"%\"\n";
    temp << "first=system(\"awk -F',' 'END {print $2}' " << file_name.c_str() <<"\")\n";
    temp << "plot \"" << file_name.c_str() << "\" using 1:(($2-first)*100/first) with lines title \"" << file_name.c_str() << "\"\n";

}

void Plot::display() {
    Gnuplot temp;
    setup_gnuplot(temp);

    temp << "filenames = \"" << file_names.c_str() << "\"\n";
    temp << "plot for [file in filenames] file using 1:2 with lines title file\n";
}

void Plot::cleanup() {
    std::istringstream iss(file_names);
    std::vector<std::string> files{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
    for (size_t i{0}; i < files.size(); i++)
        remove(files[i].c_str());
}

Plot::~Plot() {
    cleanup();
}
