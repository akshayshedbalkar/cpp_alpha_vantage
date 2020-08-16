#include <iostream>

#include "stock.h"

Stock::Stock() {
}

Stock::Stock(Api* a, Plot* p, std::string s) : symbol{s}, api{a}, plot{p} {
}

void Stock::fetch_data(std::string function) {
    api->fetch_data(function, symbol, stock_data);
    plot->process_data(stock_data);
    plot->create_temp_file(stock_data,symbol);
}

void Stock::display_data() {
    plot->display_stock_data(symbol);
}
