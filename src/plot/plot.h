/**
 * @file plot.h
 * @brief Plot class
 * @author Akshay Shedbalkar
 * @version 1.0
 * @date 2022-08-13
 */
#ifndef PLOT_H
#define PLOT_H

#include <string> // for string
#include <vector> // for vector

#include "gnuplot-iostream.h" // for Gnuplot

/**
 * @brief 0: Create new plot. 1: Redraw on existing plot.
 */
enum class Plot_type;

/**
 * @brief Wraps gnuplot to plot stock data
 */
class Plot
{
private:
  std::vector<std::string>
    file_names; /*!< Array of file names, each holding csv data for one stock */
  std::string function;               /*!< Daily / weekly / monthly data */
  static std::string csv_column_name; /*!< Open / close / adjusted  */
  static int csv_column;      /*!< Left to right position of csv_column_name */
  static float time_in_weeks; /*!< Time in weeks */

public:
  /**
   * @brief Default constructor
   */
  Plot();
  /**
   * @brief Constructor
   *
   * @param s csv_column_name
   * @param time time in weeks
   */
  Plot(std::string s, float time);

  /**
   * @brief Getter
   *
   * @return time_in_weeks
   */
  static float get_time_in_weeks();

  /**
   * @brief Plot data for all stocks
   */
  void display() const;
  /**
   * @brief Plot data for a single stock
   *
   * @param s Stock name
   */
  void display(std::string const &s) const;

  /**
   * @brief Setup options for gnuplot
   *
   * @param g Gnuplot object
   */
  void setup_gnuplot(Gnuplot &g) const;
  /**
   * @brief Figure out which column to plot, comment out first row for gnuplot
   * and remove all carriage returns
   *
   * @param s Stock data from csv file
   */
  void process_data(std::string &s) const;
  /**
   * @brief Calculate furthest point back in time upto which to plot
   * (time_in_weeks). The point is saved in a variable on the command line in
   * gnuplot.
   *
   * @param g Gnuplot object
   * @param file_name File name containing data for a stock.
   */
  void get_first_datapoint(Gnuplot &g, std::string const &file_name) const;
  /**
   * @brief Plot data from time_in_weeks up until today. Oldest datapoint is
   * normalized for all stocks.
   *
   * @param g Gnuplot object
   * @param file_name File name of data for a stock
   * @param type First plot is created new, subsequent plots are redrawn on the
   * first plot.
   */
  void percentage_plot(Gnuplot &g,
                       std::string const &file_name,
                       const Plot_type type) const;
  /**
   * @brief Set to daily / weekly / monthly data
   *
   * @param function Daily / Weekly / Monthly
   */
  void set_function(std::string const &function);

  /**
   * @brief Create a file to store stock data. Will be deleted at end of
   * program.
   *
   * @param data Stock data
   * @param file_name File name
   */
  void create_temp_file(std::string const &data, std::string const &file_name);
  /**
   * @brief Delete files storing stock data.
   */
  void cleanup() const;

  /**
   * @brief Destructor cleans up temporaray files storing stock data.
   */
  ~Plot();
};

#endif /* ifndef PLOT_H */
