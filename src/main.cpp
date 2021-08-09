#include "api.h"
#include "plot.h"
#include "stock.h"

#include <iostream>
#include <string>

struct Config
{
    int start;
    int length;
};

static void read_config(const std::string &config_file_name, std::vector<std::string> &config);

int main()
{
    constexpr Config certificate_config{.start = 0, .length = 12};
    constexpr Config license_config{.start = 1, .length = 7};
    constexpr Config function_config{.start = 2, .length = 9};
    constexpr Config csv_column_config{.start = 3, .length = 7};
    constexpr Config stock_config{.start = 4, .length = 6};

    // Read in config file
    std::vector<std::string> config;
    read_config("stocks.config", config);

    // Get license information from config file
    std::string my_apikey = "demo";
    my_apikey = config[license_config.start].substr(license_config.length);

    if (my_apikey == "demo")
    {
        std::cout << "Warning: You are using API key \"demo\". Stocks other than IBM will not work!" << std::endl;
    }

    // Get path to certificate for curl access
    std::string my_cert_path = config[certificate_config.start].substr(certificate_config.length);

    // configure alphavantage and curl. This is only required once.
    Api api(my_apikey, my_cert_path);

    // configure gnuplot. This is required only once.
    std::string csv_column = config[csv_column_config.start].substr(csv_column_config.length);
    Plot plot(csv_column);

    // Get stock names from config file and create Stock objects
    std::vector<std::string> stock_names(config.begin() + stock_config.start, config.end());
    std::for_each(stock_names.begin(), stock_names.end(), [](std::string &s) { s = s.substr(stock_config.length); });

    std::vector<Stock> stocks;
    for (const auto &stock_name : stock_names)
    {
        stocks.push_back(Stock(&api, &plot, stock_name));
    }

    if (stocks.size() > 5)
    {
        std::cout
            << "Warning: You are trying to fetch data for more than 5 symbols at a time. This is not possible with a "
               "free API key. Data fetched might be garbage."
            << std::endl;
    }

    // Get time function from config file and fetch stock data
    std::string time_function = config[function_config.start].substr(function_config.length);

    for (auto &stock : stocks)
    {
        stock.fetch(time_function);
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

static void read_config(const std::string &config_file_name, std::vector<std::string> &config)
{
    std::ifstream config_file(config_file_name.c_str());
    std::copy(std::istream_iterator<std::string>(config_file), std::istream_iterator<std::string>(),
              back_inserter(config));
}
