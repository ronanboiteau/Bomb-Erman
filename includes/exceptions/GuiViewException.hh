#ifndef GUIVIEW_EXCEPTION_HH_
# define GUIVIEW_EXCEPTION_HH_

# include <exception>
# include <string>

class		GuiViewException : public std::exception
{
private:
  std::string	_msg;
public:
  GuiViewException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~GuiViewException() = default;
};

#endif /* !CONFIGURATION_EXCEPTION_HH_ */
