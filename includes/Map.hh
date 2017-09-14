#ifndef MAP_HH_
# define MAP_HH_

# include <chrono>
# include <irrlicht.h>
# include <cstddef>
# include <vector>
# include <string>
# include "MeshesLoader.hh"
# include "ImagesLoader.hh"
# include "BoxType.hh"
# include "Position.hh"

class ABox;

class		Map final
{
private:
  size_t			_density;
  irr::IrrlichtDevice		*_device;
  MeshesLoader			*_meshLoader;
  ImagesLoader			*_imgLoader;
  size_t			_size;
  size_t			_nb_unbreakable;
  std::vector<std::vector<ABox *> > _map;
  void				create_map(size_t density);
  void				create_map();
  void				put_breakable_blocks(size_t density);
  bool				is_safe_block(Position pos);
  irr::video::IVideoDriver	*_driver;
  irr::scene::ISceneManager	*_sceneManager;
  irr::scene::ICameraSceneNode	*_camera;
  irr::scene::IMeshSceneNode	*_board;

public:
  Map(size_t size, size_t density, irr::IrrlichtDevice *device, MeshesLoader *meshLoader, ImagesLoader *img_loader);
  Map(const std::string &file_path, irr::IrrlichtDevice *device, MeshesLoader *meshLoader, ImagesLoader *img_loader);
  Map(const Map &map) = delete;
  Map				&operator=(const Map &map) = delete;
  ABox				*Get_element(const Position &pos) const;
  bool				Is_out_of_range(const Position &pos) const;
  void				Set_element(const Position &pos, ABox *box);
  void				Set_element(const Position &pos, BoxType::eBoxType type);
  const std::vector<std::vector<ABox *> >	&Get_map() const;
  ~Map();
  void				Print_map(); //pour debug
  void				Try_explode_bombs();
  size_t			Get_size() const;
  size_t			Get_density() const;
  irr::IrrlichtDevice		&Get_device();
  irr::video::IVideoDriver	&Get_driver();
  irr::scene::ISceneManager	&Get_scene_manager();
  irr::scene::ICameraSceneNode	&Get_camera();
  void				Add_to_timer(std::chrono::milliseconds const &t);
};

#endif /* !MAP_HH_ */
