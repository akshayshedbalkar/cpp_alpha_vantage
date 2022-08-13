/**
 * @file stock.h
 * @brief Stock class
 * @author Akshay Shedbalkar
 * @version 1.0
 * @date 2022-08-13
 */
#ifndef STOCK_H
#define STOCK_H

#include <string> // for string

class Api;
class Plot;

/**
 * @brief Stores information about a stock and handles its functions
 */
class Stock
{
private:
  Api *api;               /*!< API object handle */
  Plot *plot;             /*!< Gnuplot object handle */
  std::string stock_data; /*!< Historical data of the stock */
  std::string symbol;     /*!< Symbol of the stock */

public:
  /**
   * @brief Default constructor
   */
  Stock();
  /**
   * @brief Constructor
   *
   * @param a API handle for alphavantage and curl
   * @param p Plot handle for gnuplot
   * @param s Stock symbol name
   */
  Stock(Api *a, Plot *p, std::string const &s);

  /**
   * @brief Fetch historical stock data
   *
   * @param function Daily / Weekly / Monthly
   */
  void fetch(std::string const &function);
  /**
   * @brief Plot stock data
   */
  void display() const;
};

#endif /* ifndef STOCK_H */
