#ifndef IMAGES_LOADER_EXCEPTION_HH_
# define IMAGES_LOADER_EXCEPTION_HH_

# include <exception>
# include <string>

class		ImagesLoaderException : public std::exception
{
private:
  std::string	_msg;
public:
  ImagesLoaderException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~ImagesLoaderException() = default;
};

#endif /* !IMAGES_LOADER_EXCEPTION_HH_ */
