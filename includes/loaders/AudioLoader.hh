#ifndef AUDIO_LOADER_HH_
# define AUDIO_LOADER_HH_

# include <irrKlang.h>
# include <string>
# include <unordered_map>
# include <thread>
# include "Configuration.hh"
# include "MonitoredLoader.hh"

class		AudioLoader final : public MonitoredLoader
{
private:
  bool		_fu_is_joined;
  std::thread	_fu;
  void		loader(irrklang::ISoundEngine *sound_engine,
		       const std::string &sounds_dir_str,
		       const std::string &musics_dir_str);
  std::unordered_map<std::string, irrklang::ISoundSource*>	_sounds;
  std::unordered_map<std::string, irrklang::ISoundSource*>	_musics;
public:
  AudioLoader(irrklang::ISoundEngine *sound_engine);
  AudioLoader(const AudioLoader &other_copy) = delete;
  AudioLoader	&operator=(const AudioLoader &other_affectation_copy) = delete;
  void		Joiner();
  irrklang::ISoundSource	*Get_sound(const std::string &sound);
  irrklang::ISoundSource	*Get_music(const std::string &music);
  // void	Set_finish();
  // Toutes les capacités pour chopper les ressources
  ~AudioLoader(); // Join les threads ?
};

#endif /* !AUDIO_LOADER_HH_ */
