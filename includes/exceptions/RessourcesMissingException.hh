#ifndef RESSOURCES_MISSING_EXCEPTION_HH_
# define RESSOURCES_MISSING_EXCEPTION_HH_

# include <exception>
# include <string>

class		RessourcesMissingException : public std::exception
{
private:
  std::string	_msg;
public:
  RessourcesMissingException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~RessourcesMissingException() = default;
};

#endif /* !RESSOURCES_MISSING_EXCEPTION_HH_ */
