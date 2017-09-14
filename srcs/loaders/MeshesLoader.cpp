#include "MyDirectory.hh"
#include "MyDirectoryException.hh"
#include "MeshesLoader.hh"
#include "MeshesLoaderException.hh"
#include "ExtensionsValidator.hh"

void		MeshesLoader::loader(irr::scene::ISceneManager *scene,
				     const std::string &meshes_dir_str)
{
  try
    {
      bool	finished{false};
      MyDirectory	meshes_dir{meshes_dir_str};
      ExtensionsValidator	meshes_extensions{std::vector<std::string>{".md2", ".3ds"}};

      while (finished == false)
	{
	  std::string	tmp_path{meshes_dir_str};

	  tmp_path += meshes_dir.Get_next_filepath(finished);
	  if (!finished && meshes_extensions(tmp_path)
	      && (_meshes[tmp_path] = scene->getMesh(std::move(tmp_path.c_str()))) == nullptr)
	    throw (MeshesLoaderException("Cannot load a meshes"));
	}
      Set_loading_finished();
      return ;
    }
  catch (std::exception &e)
    {
      Set_loading_error(e.what());
    }
}

MeshesLoader::MeshesLoader(irr::scene::ISceneManager *scene_manager)
{
  loader(scene_manager, "indie_ressources/assets/");
}

irr::scene::IAnimatedMesh	*MeshesLoader::Get_mesh(const std::string &path)
{
  return (_meshes.at(path));
}
