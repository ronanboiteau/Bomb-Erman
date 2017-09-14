#ifndef MESHES_LOADER_HH_
# define MESHES_LOADER_HH_

# include <irrlicht.h>
# include <unordered_map>
# include <string>
# include "MonitoredLoader.hh"

class		MeshesLoader final : public MonitoredLoader
{
private:
  std::unordered_map<std::string, irr::scene::IAnimatedMesh*>	_meshes;
  void			loader(irr::scene::ISceneManager *scene,
			       const std::string &meshes_dir_str);
public:
  MeshesLoader(irr::scene::ISceneManager *scene_manager);
  MeshesLoader(const MeshesLoader &other_copy) = delete;
  irr::scene::IAnimatedMesh	*Get_mesh(const std::string &path);
  MeshesLoader &operator=(const MeshesLoader &other_affectation_copy) = delete;
};

#endif /* !MESHES_LOADER_HH_ */
