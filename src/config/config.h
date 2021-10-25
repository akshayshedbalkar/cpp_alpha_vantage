#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

class Config
{
  private:
    int start;
    int length;

    static std::vector<std::string> config_data;

  public:
    Config();
    Config(int s, int l);

    int get_start();
    int get_length();

    std::string get_config();

    static void read(const std::string &config_file_name);

    static auto begin()
    {
        return config_data.begin();
    }
    static auto end()
    {
        return config_data.end();
    }
};

#endif /* ifndef CONFIG_H */
