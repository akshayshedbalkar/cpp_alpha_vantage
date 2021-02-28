#include <iostream>

#include "stock.h"

Stock::Stock() {
}

Stock::Stock(Api* a, Plot* p, std::string s) : symbol{s}, api{a}, plot{p} {
}

void Stock::fetch(std::string function) {
    api->fetch(function, symbol, stock_data);
    plot->process_data(stock_data);
    plot->create_temp_file(stock_data, symbol);
}

void Stock::display() {
    plot->display(symbol);
}
