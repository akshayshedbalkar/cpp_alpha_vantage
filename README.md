# cpp_alpha_vantage

This project uses the Alpha Vantage API with C++ to fetch data and plot it on a chart. The goal is to achieve a user friendly python-like interface.   

### Brief overview
The project consists of 3 classes wrapping the functionalities of Alpha vantage API access (through curl), plotting (with gnuplot) and data storage of stocks. 
The project is quite rudimentary and supports the following:

- Time data about any symbol can be fetched and percentage change in values can be plotted
- Time data of various symbols can be fetched and percentage change in values can be plotted on the same plot

### Basic usage:

1. Store your Alpha Vantage API key ( get it free from here: https://www.alphavantage.co/) in a string. The path to a certificate also needs to be given for curl access. 
A certificate is provided in extern/certs. 

```c++
std::string my_apikey = "demo";
std::string my_cert_path = "E:\\programming\\cpp\\stocks\\extern\\certs\\curl-ca-bundle.crt";
```    
2. Declare Api and Plot objects. The Api class wraps API access and the Plot class wraps gnuplot plotting tools. This only needs to be done once.

```c++
Api api(my_apikey, my_cert_path);//configure alphavantage and curl
Plot plot;//configure gnuplot.
```

3. For each symbol, declare a Stock object. Api and Plot handles are needed in the declaration. The same handles may be used for all Stock objects. 
```c++
Stock stock1(&api, &plot, "IBM");
Stock stock2(&api, &plot, "GOOGL");
```

4. Now, symbol data can be fetched and plotted. 
```c++
stock1.fetch_data("TIME_SERIES_MONTHLY");
stock2.fetch_data("TIME_SERIES_WEEKLY");

//Show all plots on one chart
plot.display();
//Or show each plot on separate chart
stock1.display_data();
stock2.display_data();
```
Note that all charts wil be shown one after another. You can put all stock objects in a `std::vector`and fetch data in a loop. Note however, that the free Alpha Vange API key only allow 5 calls at a time. 

### Dependencies

- curl (https://curl.haxx.se/)
- gnuplot (http://www.gnuplot.info/)
- boost (https://www.boost.org/)

### Building the program

If dependencies (curl, gnuplot, boost) are installed, building is as simple as:
```bash
mkdir build
cd build
cmake ..
make
```
