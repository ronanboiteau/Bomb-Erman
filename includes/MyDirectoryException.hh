#ifndef MY_DIRECTORY_EXCEPTION_HH_
# define MY_DIRECTORY_EXCEPTION_HH_

# include <exception>
# include <string>

class		MyDirectoryException : public std::exception
{
private:
  std::string	_msg;
public:
  MyDirectoryException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~MyDirectoryException() = default;
};

#endif /* !MY_DIRECTORY_EXCEPTION_HH_ */
