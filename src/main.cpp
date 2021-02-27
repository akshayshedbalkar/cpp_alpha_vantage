#include <iostream>
#include <string>

#include "api.h"
#include "plot.h"
#include "stock.h"

int main() {
    std::string my_apikey = "demo";
    std::string my_cert_path = "E:\\programming\\cpp\\stocks\\extern\\certs\\curl-ca-bundle.crt";

    //configure alphavantage and curl. This is only required once. 
    Api api(my_apikey, my_cert_path);

    //configure gnuplot. This is required only once. 
    Plot plot;

    //Create Stock objects. For "Demo" apikey, only IBM works. Use own key for other symbols. 
    Stock stock1(&api, &plot, "IBM");
    /* Stock stock2(&api, &plot, "GOOGL"); */
    /* Stock stock3(&api, &plot, "NVDA"); */

    //Fetch stock data
    stock1.fetch_data("TIME_SERIES_MONTHLY");
    /* stock2.fetch_data("TIME_SERIES_MONTHLY"); */
    /* stock3.fetch_data("TIME_SERIES_MONTHLY"); */

    //show each plot of separate chart
    stock1.display_data();
    /* stock2.display_data(); */
    /* stock3.display_data(); */

    //show all plots on one chart
    plot.display();

    return 0;
}
