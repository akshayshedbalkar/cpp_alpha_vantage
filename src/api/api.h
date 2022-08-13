#ifndef API_H
#define API_H

#include <stddef.h>  // for size_t
#include <string>    // for string

#include "curl.h"  // for CURL, CURLcode

size_t callback(void* contents,
                size_t size,
                size_t nmemb,
                std::string* s);  // Member function pointer is different than
                                  // ordinary function pointer

class Api
{
 private:
  CURL* api_handle;
  CURLcode curl_result;

  std::string apikey;
  std::string base_url;

 public:
  Api();
  Api(std::string apikey, std::string cert_path);

  void fetch(std::string const& function,
             std::string const& symbol,
             std::string& stock_data);

  ~Api();
};

#endif /* ifndef API_H */
