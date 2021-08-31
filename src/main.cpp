#include "api.h"
#include "config.h"
#include "plot.h"
#include "stock.h"

#include <iostream>
#include <string>

int main()
{
    try
    {
        // Read in config file
        Config::read_config("stocks.config");

        // Initialize config objects
        Config certificate_config{0, 12}, license_config{1, 7}, function_config{2, 9}, csv_column_config{3, 7}, time_config{4, 5}, stock_config{5, 6};

        // Configure alphavantage and curl. This is only required once.
        Api api(license_config.get_config(), certificate_config.get_config());

        if (license_config.get_config() == "demo")
        {
            throw "Warning: You are using API key \"demo\". Stocks other than IBM might not work.";
        }

        // configure gnuplot. This is required only once.
        Plot plot(csv_column_config.get_config(), std::stof(time_config.get_config()));

        // Get stock names from config file and create Stock objects
        std::vector<std::string> stock_names(Config::begin() + stock_config.get_start(), Config::end());
        std::for_each(stock_names.begin(), stock_names.end(), [&](std::string &s) { s = s.substr(stock_config.get_length()); });

        std::vector<Stock> stocks;
        for (const auto &stock_name : stock_names)
        {
            stocks.push_back(Stock(&api, &plot, stock_name));
        }

        if (stocks.size() > 5)
        {
            throw "Warning: You are trying to fetch data for more than 5 symbols at a time. This is not possible with a free API key.";
        }

        // Fetch stock data
        for (auto &stock : stocks)
        {
            stock.fetch(function_config.get_config());
        }

        // show each plot of separate chart
        /* for (const auto &stock : stocks) */
        /* { */
        /*     stock.display(); */
        /* } */

        // show all plots on one chart
        plot.display();
    }

    catch (const char *s)
    {
        std::cerr << s;
    }

    catch (int i)
    {
        exit(1);
    }

    return 0;
}
