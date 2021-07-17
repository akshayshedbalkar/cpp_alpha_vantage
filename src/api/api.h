#ifndef API_H
#define API_H

#include "curl.h"

#include <string>

size_t callback(void *contents, size_t size, size_t nmemb,
                std::string *s); // Member function pointer is different than
                                 // ordinary function pointer

class Api
{
  private:
    CURL *api_handle;
    CURLcode curl_result;

    std::string apikey;
    std::string base_url;

  public:
    Api();
    Api(std::string apikey, std::string cert_path);

    void fetch(const std::string &function, const std::string &symbol, std::string &stock_data);

    ~Api();
};

#endif /* ifndef API_H */
