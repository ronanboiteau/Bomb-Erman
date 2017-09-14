#ifndef RESSOURCES_LOADER_HH_
# define RESSOURCES_LOADER_HH_

# include "IrrlichtEnvFinder.hh"
# include "RessourcesMenuLoader.hh"
# include "AudioLoader.hh"
# include "ImagesLoader.hh"
# include "MeshesLoader.hh"
# include "GameParameters.hh"

class			RessourcesLoader final
{
private:
  RessourcesMenuLoader	_menu;
  AudioLoader		_audio;
  ImagesLoader		_images;
  MeshesLoader		_meshes;
public:
  RessourcesLoader(IrrlichtEnvFinder &irr_env);
  RessourcesMenuLoader	*Get_ressources_menu();
  AudioLoader		*Get_audio_loader();
  ImagesLoader		*Get_images_loader();
  MeshesLoader		*Get_meshes_loader();
  RessourcesLoader(const RessourcesLoader &other_copy) = delete;
  RessourcesLoader	&operator=(const RessourcesLoader &other_affectation_copy) = delete;
  ~RessourcesLoader() = default;
};

#endif /* !RESSOURCES_LOADER_HH_ */
