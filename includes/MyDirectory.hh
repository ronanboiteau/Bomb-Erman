#ifndef MY_DIRECTORY_HH_
# define MY_DIRECTORY_HH_

# include <string>
# ifdef _WIN32
#  include <windows.h>
#  include <tchar.h>
# endif
# ifdef __linux__
#  include <sys/types.h>
#  include <dirent.h>
#  include <errno.h>
# endif

class			MyDirectory final
{
private:
  bool			_first;
  bool			_finished;
  std::string	_filepath;
  std::string		_last_file;
# ifdef _WIN32
  HANDLE		_handler;
# endif /* !_WIN32 */
# ifdef __linux__
  DIR			*_handler;
# endif /* !__linux__ */
public:
  MyDirectory(const std::string &filepath_dir);
  MyDirectory(const MyDirectory &other_copy) = delete;
  MyDirectory	&operator=(const MyDirectory &other_affectation_copy) = delete;
  const std::string	&Get_next_filepath(bool &end);
  ~MyDirectory();
};

#endif /* !MY_DIRECTORY_HH_ */
