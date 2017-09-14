#ifndef DIRECTORY_LOADER_HH_
# define DIRECTORY_LOADER_HH_

# include <string>
# include <vector>

class	DirectoryLoader
{
protected:
  std::vector<std::string>	_filenames;
  std::string			_directory_path;
public:
  DirectoryLoader(const std::string &directory_path,
		  const std::vector<std::string> &filenames);
  DirectoryLoader(const DirectoryLoader &other_copy) = delete;
  DirectoryLoader	&operator=(const DirectoryLoader &other_copy) = delete;
  ~DirectoryLoader() = default;
};

#endif /* !DIRECTORY_LOADER_HH_ */
