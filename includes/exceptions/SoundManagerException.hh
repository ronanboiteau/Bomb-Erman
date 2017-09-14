#ifndef SOUNDMANAGER_EXCEPTION_HH_
# define SOUNDMANAGER_EXCEPTION_HH_

# include <exception>
# include <string>

class		SoundManagerException : public std::exception
{
private:
  std::string	_msg;
public:
  SoundManagerException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~SoundManagerException() = default;
};

#endif /* !SOUNDMANAGER_EXCEPTION */
