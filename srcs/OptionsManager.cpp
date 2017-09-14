#include <fstream>
#include "OptionsManager.hh"
#include "SizeTConverter.hh"
#include "Configuration.hh"
#include "OptionsManagerException.hh"

OptionsManager::OptionsManager(const std::string &filename,
			       SoundManager *sound_manager) :
  _sounds_volume{50},
  _musics_volume{50},
  _vsync{true},
  _sound_manager{sound_manager}
{
  _file = filename;
  try {
    Configuration	config_options_file{filename, std::vector<std::string>{
	{"sounds_volume:"},
	  {"musics_volume:"},
	    {"vsync_status:"}
      }};
    SizeTConverter	converter;
    bool			converter_status[2];
    size_t		l_sounds_volume{converter.atoi(config_options_file.Get_var_value("sounds_volume:"), converter_status[0])};
    size_t		l_musics_volume{converter.atoi(config_options_file.Get_var_value("musics_volume:"), converter_status[1])};
    size_t		l_vsync{converter.atoi(config_options_file.Get_var_value("vsync_status:"))};
    if (!converter_status[0] || !converter_status[1] || (l_vsync != 0 && l_vsync != 1))
      throw OptionsManagerException("Error during conversion of a value in the options file");
    Set_musics_volume(l_musics_volume);
    Set_sounds_volume(l_sounds_volume);
    _vsync = l_vsync;
  }
  catch (std::exception &e)
    {
      std::cerr << " Invalids settings, using default values" << std::endl;
      _sounds_volume = 50;
      _musics_volume = 50;
      _vsync = true;
    }
}

size_t	OptionsManager::Get_sounds_volume() const
{
  return (_sounds_volume);
}

size_t	OptionsManager::Get_musics_volume() const
{
  return (_musics_volume);
}

bool	OptionsManager::Get_vsync() const
{
  return (_vsync);
}

void	OptionsManager::Set_musics_volume(size_t new_value)
{
  if (new_value > 100)
    throw OptionsManagerException("Invalid value for musics volume");
  _musics_volume = new_value;
  _sound_manager->Set_music_volume(_musics_volume);
}

 void	OptionsManager::Set_sounds_volume(size_t new_value)
{
  if (new_value > 100)
    throw OptionsManagerException("Invalid value for sounds volume");
  _sounds_volume = new_value;
  _sound_manager->Set_sound_volume(_sounds_volume);
}

void	OptionsManager::Set_vsync(bool vsync)
{
  _vsync = vsync;
}

std::ostream	&operator<<(std::ostream &os, const OptionsManager &to_dump)
{
  os << "sounds_volume:" << to_dump.Get_sounds_volume() << std::endl;
  os << "musics_volume:" << to_dump.Get_musics_volume() << std::endl;
  os << "vsync_status:" << to_dump.Get_vsync() << std::endl;
  return (os);
}

OptionsManager::~OptionsManager()
{
  std::ofstream	file_save{_file};
  file_save << *this;
}
