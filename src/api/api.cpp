#include "api.h"
#include "curl.h"
#include "plot.h"

#include <iostream>

size_t callback(void *contents, size_t size, size_t nmemb, std::string *g)
{
    size_t newLength{size * nmemb};
    g->append((char *)contents, newLength);
    return newLength;
}

Api::Api() : Api{"demo", "C:\\curl-ca-bundle.crt"}
{
}

Api::Api(std::string apikey, std::string cert_path) : curl_result{CURLE_OK}, apikey{apikey}, base_url{"https://www.alphavantage.co/query?"}
{
    curl_global_init(CURL_GLOBAL_ALL);
    api_handle = curl_easy_init();
    curl_easy_setopt(api_handle, CURLOPT_CAINFO, cert_path.c_str());
}

void Api::fetch(const std::string &function, const std::string &symbol, std::string &stock_data)
{
    std::string url{base_url};

    url += "function=" + function;
    url += "&symbol=" + symbol;
    if (function == "TIME_SERIES_INTRADAY")
    {
        url += "&interval=5min";
    }
    url += "&apikey=" + apikey;

    constexpr int days_in_a_week{6}, max_days_in_compact_call{100};
    if (Plot::get_time_in_weeks() * days_in_a_week >= max_days_in_compact_call)
    {
        url += "&outputsize=full";
    }

    url += "&datatype=csv";

    curl_easy_setopt(api_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(api_handle, CURLOPT_WRITEDATA, &stock_data);
    curl_easy_setopt(api_handle, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(api_handle, CURLOPT_FOLLOWLOCATION, 1L);

    curl_result = curl_easy_perform(api_handle);

    if (curl_result != CURLE_OK)
    {
        throw "curl_easy_perform() failed.";
        throw curl_easy_strerror(curl_result);
        throw -1;
    }
}

Api::~Api()
{
    curl_easy_cleanup(api_handle);
    curl_global_cleanup();
}
