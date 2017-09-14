#ifndef SIZET_CONVERTER_EXCEPTION_HH_
# define SIZET_CONVERTER_EXCEPTION_HH_

# include <exception>
# include <string>

class		SizeTConverterException : public std::exception
{
private:
  std::string	_msg;
public:
  SizeTConverterException(const std::string &message) : _msg{message}{};
  SizeTConverterException(const std::wstring &message) : _msg{message.begin(), message.end()}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~SizeTConverterException() = default;
};

#endif /* !SIZET_CONVERTER_EXCEPTION_HH_ */
