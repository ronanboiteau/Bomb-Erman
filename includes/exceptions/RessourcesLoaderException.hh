#ifndef RESSOURCES_LOADER_EXCEPTION_HH_
# define RESSOURCES_LOADER_EXCEPTION_HH_

# include <exception>
# include <string>

class		RessourcesLoaderException : public std::exception
{
private:
  std::string	_msg;
public:
  RessourcesLoaderException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~RessourcesLoaderException() = default;
};

#endif /* !RESSOURCES_LOADER_EXCEPTION_HH_ */
