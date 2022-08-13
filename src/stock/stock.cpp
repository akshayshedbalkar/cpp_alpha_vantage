#include "stock.h"

#include "api.h"  // for Api
#include "plot.h" // for Plot

Stock::Stock() {}

Stock::Stock(Api *a, Plot *p, std::string const &s)
  : symbol{ s }
  , api{ a }
  , plot{ p }
{
}

void
Stock::fetch(std::string const &function)
{
  stock_data.clear();
  api->fetch(function, symbol, stock_data);
  plot->process_data(stock_data);
  plot->create_temp_file(stock_data, symbol);
  plot->set_function(function);
}

void
Stock::display() const
{
  plot->display(symbol);
}
