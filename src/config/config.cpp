#include "config.h"

#include <algorithm>
#include <fstream>
#include <iterator>

std::vector<std::string> Config::config_data{};

int Config::get_length()
{
    return length;
}
int Config::get_start()
{
    return start;
}

std::string Config::get_config()
{
    return config_data[start].substr(length);
}

Config::Config()
{
}

Config::Config(int s, int l) : start{s}, length{l}
{
}

void Config::read(const std::string &config_file_name)
{
    std::ifstream config_file(config_file_name.c_str());
    std::copy(std::istream_iterator<std::string>(config_file), std::istream_iterator<std::string>(), back_inserter(config_data));
}
