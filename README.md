# cpp_alpha_vantage
Using Alpha Vantage API with C++

This barebones project uses the Alpha Vantage API with C++. 

### Dependencies

- curl
- gnuplot
- boost

### Brief overview
The project consists of 3 classes wrapping the functionalities of Alpha vantage API access (through curl), plotting (with gnuplot) and data storage of stocks. 
The project is quite rudimentary and supports the following:

- Time data about any symbol can be fetched and absolute values can be plotted
- Time data of various symbols can be fetched and absolute values can be plotted on the same plot

### Basic usage:

1. Store your Alpha Vantage API key ( get it free from here: https://www.alphavantage.co/) in a string. The path to a certificate also needs to be given for curl access. 
A certificate is provided in extern/certs. 

```c++
std::string my_apikey = "demo";
std::string my_cert_path = "E:\\programming\\cpp\\stocks\\extern\\certs\\curl-ca-bundle.crt";
```    
2. Declare Api and Plot objects. The Api class wraps API access and the Plot class wraps gnuplot plotting tools. 

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
Note that all charts wil be shown one after another. 

### TODO

To make this project better, the following needs to be done. A lot of these goals can be accomplished by implementing a csv parser 
which converts the csv string into a 2D vector of doubles.  

- When plotting all symbols on one chart, show percentage increase rather than absolute values. Some deeper knowledge of gnuplot is required here. 
- Remove csv files after program exit. Removing files in the destructor does not seem to work. The destructor is called before the gnuplot stream leading to no data to plot. 
- Plot data as candlestick chart.
- Extra overloaded functions to use optional features of Alpha Vantage API.
- Show all charts simultaneously instead of one by one. I do not know if this is a limitation of gnuplot c++ interface. 







