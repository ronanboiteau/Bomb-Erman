#include "MyDirectory.hh"
#include "MyDirectoryException.hh"

MyDirectory::MyDirectory(const std::string &filepath_dir) :
	_first{ true },
	_finished{ false },
	_filepath{ filepath_dir }
{
#ifdef _WIN32
	WIN32_FIND_DATA	ffd;
	_filepath += "\\*";
 	_handler = FindFirstFile(_filepath.c_str(), &ffd);
	if (_handler == INVALID_HANDLE_VALUE)
		throw MyDirectoryException("Invalid directory");
	_last_file = ffd.cFileName;
#endif /* !_WIN32 */
#ifdef __linux__
	if ((_handler = opendir(filepath_dir.c_str())) == NULL)
		throw MyDirectoryException("error during directory reading");
#endif /* !__linux__ */
}

const std::string	&MyDirectory::Get_next_filepath(bool &finished)
{
  finished = false;
  if (_finished)
    {
      finished = true;
      return (_last_file);
    }
#ifdef __linux__
  struct dirent		*tmp;
  errno = 0;
  if ((tmp = readdir(_handler)) == nullptr)
    {
      if (errno != 0)
	throw MyDirectoryException("An error occured");
      _finished = true;
      finished = true;
      return (_last_file);
    }
  _last_file = tmp->d_name;
#endif /* !__linux__ */
#ifdef _WIN32
  if (!_first)
    {
      WIN32_FIND_DATA	ffd;
      if (FindNextFile(_handler, &ffd) == 0)
	{
	  if (GetLastError() != ERROR_NO_MORE_FILES)
	    throw MyDirectoryException("An error occured");
	  _finished = true;
	  finished = true;
	}
      _last_file = ffd.cFileName;
    }
#endif /* !_WIN32 */
  _first = false;
  return (_last_file);
}

MyDirectory::~MyDirectory()
{
#ifdef _WIN32
	FindClose(_handler);
#endif /* !_WIN32 */
#ifdef __linux__
	closedir(_handler);
#endif /* !__linux__ */
}
