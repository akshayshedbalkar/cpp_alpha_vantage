#include <bits/chrono.h>  // for operator""s, chrono_literals
#include <stdlib.h>       // for exit
#include <algorithm>      // for for_each
#include <iostream>       // for operator<<, ostream, cerr, cout
#include <string>         // for string, allocator, operator==, stof
#include <thread>         // for sleep_for
#include <vector>         // for vector

#include "api.h"          // for Api
#include "config.h"       // for Config
#include "plot.h"         // for Plot
#include "stock.h"        // for Stock

int main()
{
    try
    {
        // Read in config file
        Config::read("stocks.config");

        // Initialize config objects
        Config certificate{0, 12}, license{1, 8}, function{2, 9}, csv_column{3, 7}, time{4, 5}, stock_config{5, 6};

        // Configure alphavantage and curl. This is only required once.
        Api api(license.get_config(), certificate.get_config());

        if (license.get_config() == "demo")
        {
            throw "Warning: You are using API key \"demo\". Stocks other than IBM might not work.";
        }

        // configure gnuplot. This is required only once.
        Plot plot(csv_column.get_config(), std::stof(time.get_config()));

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
            std::cout << "Warning: You are trying to fetch data for more than 5 symbols at a time. The program will wait 60 seconds after each set "
                         "of 5 API calls.";
        }

        // Fetch stock data
        int number_of_stocks{0};
        constexpr int limit{4};
        for (auto &stock : stocks)
        {
            if (number_of_stocks++ > limit)
            {
                number_of_stocks = 0;

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(60s);
            }

            stock.fetch(function.get_config());
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
