#include <iostream>
#include <string>

#include "api.h"
#include "plot.h"
#include "stock.h"

int main() {
    std::string my_apikey = "demo";
    std::string my_cert_path = "E:\\programming\\cpp\\stocks\\extern\\certs\\curl-ca-bundle.crt";

    Api api(my_apikey, my_cert_path);//configure alphavantage and curl
    Plot plot;//configure gnuplot.

    Stock stock1(&api, &plot, "IBM");
    Stock stock2(&api, &plot, "GOOGL");
    Stock stock3(&api, &plot, "NVDA");
    stock1.fetch_data("TIME_SERIES_MONTHLY");
    stock2.fetch_data("TIME_SERIES_MONTHLY");
    stock3.fetch_data("TIME_SERIES_MONTHLY");

    stock1.display_data();//show each plot of separate chart
    stock2.display_data();
    stock3.display_data();
    plot.display();//show all plots on one chart

    return 0;
}
