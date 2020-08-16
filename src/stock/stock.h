#ifndef STOCK_H
#define STOCK_H
#include <string>

#include "api.h"
#include "plot.h"

class Stock {
   private:
    Api *api;
    Plot *plot;
    std::string stock_data;
    std::string symbol;

   public:
    Stock();
    Stock(Api *a, Plot *p, std::string s);

    void fetch_data(std::string function);
    void display_data();
};

#endif /* ifndef STOCK_H */
