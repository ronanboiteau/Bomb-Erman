#ifndef CONFIGURATION_EXCEPTION_HH_
# define CONFIGURATION_EXCEPTION_HH_

# include <exception>
# include <string>

class		ConfigurationException : public std::exception
{
private:
  std::string	_msg;
public:
  ConfigurationException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~ConfigurationException() = default;
};

#endif /* !CONFIGURATION_EXCEPTION_HH_ */
