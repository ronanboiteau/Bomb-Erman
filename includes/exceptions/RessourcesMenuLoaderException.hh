#ifndef RESSOURCES_MENU_LOADER_EXCEPTION_HH_
# define RESSOURCES_MENU_LOADER_EXCEPTION_HH_

# include <exception>
# include <string>

class		RessourcesMenuLoaderException : public std::exception
{
private:
  std::string	_msg;
public:
  RessourcesMenuLoaderException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~RessourcesMenuLoaderException() = default;
};

#endif /* !RESSOURCES_MENU_LOADER_EXCEPTION_HH_ */
