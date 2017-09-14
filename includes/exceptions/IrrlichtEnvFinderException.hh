#ifndef IRRLICHT_ENV_FINDER_EXCEPTION_HH_
# define IRRLICHT_ENV_FINDER_EXCEPTION_HH_

# include <exception>
# include <string>

class		IrrlichtEnvFinderException : public std::exception
{
private:
  std::string	_msg;
public:
  IrrlichtEnvFinderException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~IrrlichtEnvFinderException() = default;
};

#endif /* !IRRLICHT_ENV_FINDER_EXCEPTION_HH_ */

