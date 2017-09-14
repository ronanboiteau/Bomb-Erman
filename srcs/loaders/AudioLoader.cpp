#include <iostream>
#include <thread>
#include "MyDirectory.hh"
#include "MyDirectoryException.hh"
#include "ExtensionsValidator.hh"
#include "AudioLoader.hh"
#include "AudioLoaderException.hh"

void	AudioLoader::loader(irrklang::ISoundEngine *sound_engine,
			    const std::string &sounds_dir_str,
			    const std::string &musics_dir_str)
{
  try
    {
      bool			finished{false};
      MyDirectory		sounds_dir{sounds_dir_str};
      MyDirectory		musics_dir{musics_dir_str};
      ExtensionsValidator	sounds_extensions{std::vector<std::string>{".wav"}};
      ExtensionsValidator	musics_extensions{std::vector<std::string>{".wav"}};

      while (finished == false)
      	{
      	  std::string	tmp_path{sounds_dir_str};

      	  tmp_path += sounds_dir.Get_next_filepath(finished);
      	  if (!finished && sounds_extensions(tmp_path)
      	      && (_sounds[tmp_path] = sound_engine->addSoundSourceFromFile(std::move(tmp_path.c_str()))) == nullptr)
      	    throw (AudioLoaderException("Cannot load a wav sound"));
      	}
      finished = false;
      _loading_percentage.Set_safely_value(50);
      while (finished == false)
      	{
      	  std::string	tmp_path{musics_dir_str};

      	  tmp_path += musics_dir.Get_next_filepath(finished);
      	  if (!finished && musics_extensions(tmp_path)
      	      && (_musics[tmp_path] = sound_engine->addSoundSourceFromFile(std::move(tmp_path.c_str()))) == nullptr)
      	    throw (AudioLoaderException("Cannot load a wav music"));
      	}
      Set_loading_finished();
      return ;
    }
  catch (std::exception &e)
    {
      Set_loading_error(e.what());
    }
}

AudioLoader::AudioLoader(irrklang::ISoundEngine *sound_engine) :
  _fu_is_joined{false}
{
  _fu = std::thread{&AudioLoader::loader, this, sound_engine, "indie_ressources/sounds/", "indie_ressources/musics/"};
}

void	AudioLoader::Joiner()
{
  _fu_is_joined = true;
  _fu.join();
}

irrklang::ISoundSource	*AudioLoader::Get_sound(const std::string &sound)
{
  return (_sounds[sound]);
}

irrklang::ISoundSource	*AudioLoader::Get_music(const std::string &music)
{
  return (_musics[music]);
}

AudioLoader::~AudioLoader()
{
  if (!_fu_is_joined)
    {
      _fu_is_joined = true;
      _fu.join();
    }
}
