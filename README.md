# cpp_alpha_vantage

This project uses the Alpha Vantage API with C++ to fetch data and plot it on a chart. The goal is to achieve a user friendly python-like interface.   

## Brief overview
The project consists of 3 classes wrapping the functionalities of Alpha vantage API access (through curl), plotting (with gnuplot) and data storage of stocks. 
The project supports the following:

- Time data about any symbol can be fetched and percentage change in values can be plotted
- Time data of various symbols can be fetched and percentage change in values can be plotted on the same plot

## Dependencies

- curl (https://curl.haxx.se/)
- gnuplot (http://www.gnuplot.info/)
- boost (https://www.boost.org/)

## Building the program

If dependencies (curl, gnuplot, boost) are installed, building is as simple as:
```bash
mkdir build
cd build
cmake ..
make
```

## Typical usage

1. Fill the config file `stocks.config`.
2. Execute the program. 

For most usage scenarios, recompiling the program is not neccessary. Only changes to the config file are needed. 

## Details

### Usage

Use the config file to input the Alpha Vantage API key ( get it free from here: https://www.alphavantage.co/), time function for plotting and needed stocks. 

The format of the config file is a simple key:value syntax. The first key must be the API key. The second must be the time function. The third key and onwards are stocks. 
Building the program copies the `stocks.config`file from the root directory to the build directory. 
Modify the config file which is in the directory from which you execute the program. 

```
LICENSE:DEMO12345
FUNCTION:TIME_SERIES_DAILY
STOCK:NVDA
STOCK:GOOGL
STOCK:AMZN
STOCK:AMD
STOCK:FB
```

A list of all time functions can be found here (https://www.alphavantage.co/documentation/).

### Programming


1. Curl is used for internet access. A certificate is needed for this and one is provided in extern/certs. 

2. The Api class wraps API access and the Plot class wraps gnuplot plotting tools. This only needs to be done once.

```c++
Api api(my_apikey, my_cert_path);   //configure alphavantage and curl
Plot plot;                          //configure gnuplot.
```

3. For each symbol, a Stock object needs to be declared. Api and Plot handles are needed in the declaration. The same handles may be used for all Stock objects. 
```c++
Stock stock1(&api, &plot, "IBM");
Stock stock2(&api, &plot, "GOOGL");
```

4. Now, symbol data can be fetched and plotted. 
```c++
stock1.fetch("TIME_SERIES_MONTHLY");
stock2.fetch("TIME_SERIES_WEEKLY");

//Show all plots on one chart
plot.display();

//Or show each plot on separate chart
stock1.display();
stock2.display();
```
Note that all charts wil be shown one after another. You can put all stock objects in a `std::vector`and fetch data in a loop.
Note however, that the free Alpha Vange API key only allows 5 calls at a time. 

