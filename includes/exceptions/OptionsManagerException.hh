#ifndef OPTIONS_MANAGER_EXCEPTION_HH_
# define OPTIONS_MANAGER_EXCEPTION_HH_

# include <exception>
# include <string>

class		OptionsManagerException : public std::exception
{
private:
  std::string	_msg;
public:
  OptionsManagerException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~OptionsManagerException() = default;
};

#endif /* !OPTIONS_MANAGER_EXCEPTION */
