/**
 * @file config.h
 * @brief Config class
 * @author Akshay Shedbalkar
 * @version 1.0
 * @date 2022-08-13
 */
#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

/**
 * @brief Wraps reading and processing of stocks.config file
 */
class Config
{
private:
  int start;  /*!<Position from top (line number). Starts at 0.  */
  int length; /*!< Length of identifier, including the colon. */

  static std::vector<std::string>
    config_data; /*!< An array of strings holding the configuration items
                    stripped of identifiers. */

public:
  /**
   * @brief Default constructor
   */
  Config();
  /**
   * @brief Constructor
   *
   * @param s Start: Position from top (line number). Starts at 0.
   * @param l Length: Length of identifier, including the colon:
   */
  Config(int s, int l);

  /**
   * @brief Get position of configuration item
   *
   * @return Start: Position from top (line number). Starts at 0.
   */
  int get_start();
  /**
   * @brief Get length of identifier
   *
   * @return Length: Length of identifier, including the colon:
   */
  int get_length();

  /**
   * @brief Get configuration item stripped of identifier.
   *
   * @return Configuration item
   */
  std::string get_config();

  /**
   * @brief Read strings from stocks.config file
   *
   * @param config_file_name
   */
  static void read(std::string const &config_file_name);

  /**
   * @brief First configuration item
   *
   * @return First configuration item
   */
  static auto begin() { return config_data.begin(); }
  /**
   * @brief Last configuration item
   *
   * @return Last configuration item
   */
  static auto end() { return config_data.end(); }
};

#endif /* ifndef CONFIG_H */
