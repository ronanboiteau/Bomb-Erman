#include "MyDirectory.hh"
#include "MyDirectoryException.hh"
#include "ImagesLoader.hh"
#include "ExtensionsValidator.hh"
#include "ImagesLoaderException.hh"

void		ImagesLoader::loader(irr::video::IVideoDriver *driver,
				     const std::string &images_dir_str,
				     const std::string &textures_dir_str)
{
  try
    {
      bool	finished{false};
      MyDirectory	images_dir{images_dir_str};
      MyDirectory	textures_dir{textures_dir_str};
      ExtensionsValidator	images_extensions{std::vector<std::string>{".png", ".jpg", ".bmp", ".tga"}};
      ExtensionsValidator	textures_extensions{std::vector<std::string>{".png", ".jpg", ".bmp", ".tga"}};

      while (finished == false)
      	{
      	  std::string	tmp_path{images_dir_str};

      	  tmp_path += images_dir.Get_next_filepath(finished);
      	  if (!finished && images_extensions(tmp_path)
      	      && (_images[tmp_path] = driver->getTexture(std::move(tmp_path.c_str()))) == nullptr)
      	    throw (ImagesLoaderException("Cannot load an image"));
      	}
      finished = false;
      _loading_percentage.Set_safely_value(50);
      while (finished == false)
	{
	  std::string	tmp_path{textures_dir_str};

	  tmp_path += textures_dir.Get_next_filepath(finished);
	  if (!finished && textures_extensions(tmp_path)
	      && (_textures[tmp_path] = driver->getTexture(std::move(tmp_path.c_str()))) == nullptr)
	    throw (ImagesLoaderException("Cannot load a texture"));
	}
      Set_loading_finished();
    }
  catch (std::exception &e)
    {
      Set_loading_error(e.what());
    }
}

irr::video::ITexture	*ImagesLoader::Get_image(const std::string &image_path)
{
  return (_images.at(image_path));
}

irr::video::ITexture	*ImagesLoader::Get_texture(const std::string &texture_path)
{
  return (_textures.at(texture_path));
}

ImagesLoader::ImagesLoader(irr::video::IVideoDriver *video_driver)
{
  loader(video_driver, "indie_ressources/images/", "indie_ressources/textures/");
}
