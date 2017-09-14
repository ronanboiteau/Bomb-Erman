#ifndef OPTIONS_MANAGER_HH_
# define OPTIONS_MANAGER_HH_

# include <cstddef>
# include <string>
# include <vector>
# include "GuiView.hh"
# include "SoundManager.hh"

class	OptionsManager final
{
private:
  size_t	_sounds_volume;
  size_t	_musics_volume;
  bool		_vsync;
  std::string	_file;
  SoundManager	*_sound_manager;
public:
  OptionsManager(const std::string &filename,
		 SoundManager *sound_manager);
  OptionsManager(const OptionsManager &copy) = default;
  OptionsManager	&operator=(const OptionsManager &other) = default;
  size_t	Get_sounds_volume() const;
  size_t	Get_musics_volume() const;
  bool		Get_vsync() const;
  void		Set_musics_volume(size_t new_value);
  void		Set_sounds_volume(size_t new_value);
  void		Set_vsync(bool vsync);
  ~OptionsManager();
};

std::ostream	&operator<<(std::ostream &os, const OptionsManager &to_dump);

#endif /* !OPTIONS_MANAGER_HH_ */
