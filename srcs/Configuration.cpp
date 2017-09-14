#include <fstream>
#include "Configuration.hh"
#include "ConfigurationException.hh"

Configuration::Configuration(const std::string &file_to_load, const std::vector<std::string> &var_names)
{
  std::ifstream		file{file_to_load};

  if (!file.good())
    throw ConfigurationException("Error during open configuration file");
  for (std::vector<std::string>::const_iterator it = var_names.begin();
       it != var_names.end();
       ++it)
    {
      if (!file.good())
	throw ConfigurationException("Error during reading");
      std::string	line;
      size_t		it_size{it->size()};
      std::getline(file, line);
      if (line.size() < it_size || line.substr(0, it_size) != *it)
	throw ConfigurationException("Wrong line during configuration reading");
      _values[*it] = line.substr(it_size, line.size() - it_size);
    }
}

const std::string	&Configuration::Get_var_value(const std::string &var_name) const
{
  return (_values.at(var_name));
}

const std::unordered_map<std::string, std::string>	&Configuration::Get_values() const
{
  return (_values);
}

std::ostream&	operator<<(std::ostream &os, Configuration const &to_dump)
{
  for (auto & it : to_dump.Get_values())
    os << it.first << it.second << std::endl;
  return (os);
}
