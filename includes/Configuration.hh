#ifndef CONFIGURATION_HH_
# define CONFIGURATION_HH_

# include <iostream>
# include <vector>
# include <unordered_map>
# include "IConfiguration.hh"

class		Configuration final : public IConfiguration
{
private:
  std::unordered_map<std::string, std::string>	_values;
public:
  Configuration() = default;
  Configuration(const std::string &file_to_load, const std::vector<std::string> &var_names);
  Configuration(const Configuration &other_copy) = default;
  Configuration		&operator=(const Configuration &other_affectation_copy) = delete;
  const std::string	&Get_var_value(const std::string &var_name) const;
  const std::unordered_map<std::string, std::string>	&Get_values() const;
  ~Configuration() = default;
};

std::ostream	&operator<<(std::ostream &os, Configuration const &to_dump);

#endif /* !CONFIGURATION_HH_ */
