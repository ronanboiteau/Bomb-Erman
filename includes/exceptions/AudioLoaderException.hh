#ifndef AUDIO_LOADER_EXCEPTION_HH_
# define AUDIO_LOADER_EXCEPTION_HH_

# include <exception>
# include <string>

class		AudioLoaderException : public std::exception
{
private:
  std::string	_msg;
public:
  AudioLoaderException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~AudioLoaderException() = default;
};

#endif /* !AUDIO_LOADER_EXCEPTION_HH_ */
