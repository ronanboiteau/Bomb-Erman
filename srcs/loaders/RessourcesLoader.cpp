#include "RessourcesLoader.hh"
#include "RessourcesLoaderException.hh"

RessourcesLoader::RessourcesLoader(IrrlichtEnvFinder &irr_env) :
  _menu{irr_env.Get_gui()},
  _audio{irr_env.Get_sound_engine()},
  _images{irr_env.Get_video_driver()},
  _meshes{irr_env.Get_scene_manager()}
{
  size_t	percentage{0};

  while (!_audio.Get_status(percentage))
    ;
  _audio.Joiner();
  if (!_menu.Get_loading_status()
      || !_audio.Get_loading_status()
      || !_images.Get_loading_status()
      || !_meshes.Get_loading_status())
    {
      throw RessourcesLoaderException("Error during ressources loading");
    }
}

RessourcesMenuLoader	*RessourcesLoader::Get_ressources_menu()
{
  return (&_menu);
}

AudioLoader		*RessourcesLoader::Get_audio_loader()
{
  return (&_audio);
}

ImagesLoader		*RessourcesLoader::Get_images_loader()
{
  return (&_images);
}

MeshesLoader		*RessourcesLoader::Get_meshes_loader()
{
  return (&_meshes);
}
