#ifndef SOUNDMANAGER_HH_
# define SOUNDMANAGER_HH_

#include <cstddef>
#include "AudioLoader.hh"

class		SoundManager
{
private:
  irrklang::ISoundEngine		*_engine;
  irrklang::ISound			*_music_menu;
  irrklang::ISound			*_music_game;
  irrklang::ISoundSource		*_sound_explosion;
  irrklang::ISoundSource		*_sound_powerup;
public:
  SoundManager(irrklang::ISoundEngine *engine, AudioLoader *audio_loader);
  void		Play_music_menu() const;
  void		Play_music_game() const;
  void		Play_sound_explosion() const;
  void		Play_sound_powerup() const;
  void		Set_music_volume(size_t volume) const;
  void		Set_sound_volume(size_t volume) const;
  ~SoundManager();
};

#endif
