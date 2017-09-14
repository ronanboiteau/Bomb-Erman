#ifndef SAVE_INFORMATION_HH_
# define SAVE_INFORMATION_HH_

# include <string>

class	SaveInformation final
{
private:
  bool		_save;
  std::string	_save_path;
public:
  SaveInformation();
  bool			Is_a_save() const;
  const std::string	&Get_path() const;
  void			Reset_save_info();
  void			Set_path(const std::string &path);
  ~SaveInformation() = default;
};

#endif /* !SAVE_INFORMATION_HH_ */
