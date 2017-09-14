#ifndef IMAGES_LOADER_HH_
# define IMAGES_LOADER_HH_

# include <irrlicht.h>
# include <unordered_map>
# include <string>
# include "MonitoredLoader.hh"

class		ImagesLoader final : public MonitoredLoader
{
private:
  std::unordered_map<std::string, irr::video::ITexture*>	_images;
  std::unordered_map<std::string, irr::video::ITexture*>	_textures;
  void			loader(irr::video::IVideoDriver *driver,
			       const std::string &images_dir_str,
			       const std::string &textures_dir_str);
public:
  ImagesLoader(irr::video::IVideoDriver *video_driver);
  ImagesLoader(const ImagesLoader &other_copy) = delete;
  ImagesLoader	&operator=(const ImagesLoader &other_affectation_copy) = delete;
  irr::video::ITexture	*Get_texture(const std::string &texture_path);
  irr::video::ITexture	*Get_image(const std::string &image_path);
  ~ImagesLoader() = default;
};

#endif /* !IMAGES_LOADER_HH_ */
