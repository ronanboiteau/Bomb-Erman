#ifndef SAVESEXCEPTION_HH_
# define SAVESEXCEPTION_HH_

# include <exception>
# include <string>

class		SavesException : public std::exception
{
private:
  std::string	_msg;
public:
  SavesException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~SavesException() = default;
};

#endif /* !SAVESEXCEPTION */
