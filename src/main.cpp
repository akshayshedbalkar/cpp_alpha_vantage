#include <iostream>
#include <string>

#include "api.h"
#include "plot.h"
#include "stock.h"

static void read_stocks_from_config(const std::string &config_file_name, std::vector<std::string> &stock_names);

int main()
{
    std::string my_apikey = "demo";
    if(my_apikey == "demo"){
        std::cout<<"Warning: You are using API key \"demo\". Stocks other than IBM will not work!"<<std::endl;
    }
    std::string my_cert_path = "E:\\programming\\cpp\\stocks\\extern\\certs\\curl-ca-bundle.crt";

    // configure alphavantage and curl. This is only required once.
    Api api(my_apikey, my_cert_path);

    // configure gnuplot. This is required only once.
    Plot plot;

    // Create Stock objects. For "Demo" apikey, only IBM works. Use own key for
    // other symbols.
    /* std::vector<Stock> stocks{Stock(&api, &plot, "AMZN"), Stock(&api, &plot, "GOOGL"), Stock(&api, &plot, "NVDA")};
     */

    // You can also read stock symbol names from a file
    std::vector<std::string> stock_names;
    read_stocks_from_config("stocks.config", stock_names);

    std::vector<Stock> stocks;
    for (const auto &stock_name : stock_names)
    {
        stocks.push_back(Stock(&api, &plot, stock_name));
    }

    // Fetch stock data
    for (auto &stock : stocks)
    {
        stock.fetch("TIME_SERIES_DAILY");
    }

    // show each plot of separate chart
    /* for (const auto &stock : stocks) */
    /* { */
    /*     stock.display(); */
    /* } */

    // show all plots on one chart
    plot.display();

    return 0;
}

static void read_stocks_from_config(const std::string &config_file_name, std::vector<std::string> &stock_names)
{
    std::ifstream config_file(config_file_name.c_str());
    std::copy(std::istream_iterator<std::string>(config_file), std::istream_iterator<std::string>(),
              back_inserter(stock_names));
}
