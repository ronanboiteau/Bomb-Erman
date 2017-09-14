#ifndef ICONFIGURATION_HH_
# define ICONFIGURATION_HH_

# include <string>

class	IConfiguration
{
private:
public:
  virtual const std::string	&Get_var_value(const std::string &var_name) const = 0;
  virtual ~IConfiguration() = default;
};

#endif /* !ICONFIGURATION_HH_ */
