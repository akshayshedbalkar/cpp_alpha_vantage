#ifndef STOCK_H
#define STOCK_H

#include <string>  // for string

class Api;
class Plot;

class Stock
{
  private:
    Api *api;
    Plot *plot;
    std::string stock_data;
    std::string symbol;

  public:
    Stock();
    Stock(Api *a, Plot *p, const std::string &s);

    void fetch(const std::string &function);
    void display() const;
};

#endif /* ifndef STOCK_H */
