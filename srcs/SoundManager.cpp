#include "SoundManager.hh"
#include "SoundManagerException.hh"

SoundManager::SoundManager(irrklang::ISoundEngine *engine,
			   AudioLoader *audio_loader) :
  _engine(engine)
{
  if (!_engine)
    throw SoundManagerException("Cannot run Irrklang library!");
  _music_menu = _engine->play2D(audio_loader->Get_music("indie_ressources/musics/bomberman-exp.wav"), true, true);
  _music_game = _engine->play2D(audio_loader->Get_music("indie_ressources/musics/bomberman-dance.wav"), true, true);
  _sound_explosion = audio_loader->Get_sound("indie_ressources/sounds/explosion.wav");
  _sound_powerup = audio_loader->Get_sound("indie_ressources/sounds/powerup.wav");
  Set_music_volume(50);
  Set_sound_volume(50);
}

void		SoundManager::Play_music_menu() const
{
  if (_music_game)
    _music_game->setIsPaused(true);
  if (_music_menu)
  _music_menu->setIsPaused(false);
}

void		SoundManager::Play_music_game() const
{
  if (_music_menu)
    _music_menu->setIsPaused(true);
  if (_music_game)
    _music_game->setIsPaused(false);
}

void		SoundManager::Play_sound_explosion() const
{
  if (_sound_explosion)
    _engine->play2D(_sound_explosion);
}

void		SoundManager::Play_sound_powerup() const
{
  if (_sound_powerup)
    _engine->play2D(_sound_powerup);
}

void			SoundManager::Set_music_volume(size_t volume) const
{
  irrklang::ik_f32	volume_f(volume);

  volume_f /= 100;
  if (_music_menu)
    _music_menu->setVolume(volume_f);
  if (_music_game)
    _music_game->setVolume(volume_f);
}

void			SoundManager::Set_sound_volume(size_t volume) const
{
  irrklang::ik_f32	volume_f(volume);

  volume_f /= 100;
  if (_sound_explosion)
    _sound_explosion->setDefaultVolume(volume_f);
  if (_sound_powerup)
    _sound_powerup->setDefaultVolume(volume_f);
}

SoundManager::~SoundManager()
{
}
