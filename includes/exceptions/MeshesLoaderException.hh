#ifndef MESHES_LOADER_EXCEPTION_HH_
# define MESHES_LOADER_EXCEPTION_HH_

# include <exception>
# include <string>

class		MeshesLoaderException : public std::exception
{
private:
  std::string	_msg;
public:
  MeshesLoaderException(const std::string &message) : _msg{message}{};
  const char	*what() const throw() {return _msg.c_str();};
  ~MeshesLoaderException() = default;
};

#endif /* !MESHES_LOADER_EXCEPTION_HH_ */
