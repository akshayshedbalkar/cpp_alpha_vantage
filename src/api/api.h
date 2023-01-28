/**
 * @file api.h
 * @brief Api class
 * @author Akshay Shedbalkar
 * @defgroup API
 * @{
 */

#ifndef API_H
#define API_H

#include <stddef.h> // for size_t
#include <string>   // for string

#include "curl.h" // for CURL, CURLcode

/**
 * @brief A call back function to be used with curl.
 *
 * Curl needs a function pointer as an argument which writes data to a string.
 * Unfortunately, a pointer pointing to a member function is of a different type
 * than a pointer pointing to a normal function. Curl needs a pointer to a
 * normal function. Therefore this function cannot be a member function of the
 * class Api and is declared separately.
 *
 * @param contents
 * @param size
 * @param nmemb
 * @param s
 *
 * @return
 */
size_t
callback(void *contents,
         size_t size,
         size_t nmemb,
         std::string *s); // Member function pointer is different than
                          // ordinary function pointer

/**
 * @brief Wraps alphavantage API. Fetches stock data using curl.
 */
class Api
{
private:
  CURL *api_handle;     /*!<Curl object to perform curl operations  */
  CURLcode curl_result; /*!< Return value of a curl operation */

  std::string apikey;   /*!< Personal alphavantage API key is stored here */
  std::string base_url; /*!< Base URL of alphavantage API */

public:
  /**
   * @brief Default constructor
   */
  Api();
  /**
   * @brief Constructor
   *
   * @param apikey
   * @param cert_path
   */
  Api(std::string apikey, std::string cert_path);

  /**
   * @brief Fetch stock data
   *
   * @param function Daily / weekly / monthly data
   * @param symbol Stock symbol
   * @param stock_data Fetched data is stored here
   */
  void fetch(std::string const &function,
             std::string const &symbol,
             std::string &stock_data);

  /**
   * @brief Destructor cleans up curl objects
   */
  ~Api();
};

#endif /* ifndef API_H */
/* @}*/
