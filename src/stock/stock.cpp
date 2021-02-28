#include "stock.h"

#include <iostream>

Stock::Stock()
{
}

Stock::Stock(Api *a, Plot *p, const std::string &s) : symbol{s}, api{a}, plot{p}
{
}

void Stock::fetch(const std::string &function)
{
    api->fetch(function, symbol, stock_data);
    plot->process_data(stock_data);
    plot->create_temp_file(stock_data, symbol);
    plot->set_function(function);
}

void Stock::display() const
{
    plot->display(symbol);
}
