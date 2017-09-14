#ifndef BOMB_HH_
# define BOMB_HH_

# include <chrono>
# include <vector>
# include "ACharacter.hh"
# include "ABox.hh"
# include "Map.hh"
# include "SoundManager.hh"

class	Bomb final : public ABox
{
private:
  std::chrono::time_point<std::chrono::system_clock>	_time_created;
  ACharacter						&_owner;
  bool							_exploded;
  SoundManager						*_sound_manager;
  size_t						_range;
  irr::scene::IAnimatedMesh				*_meshi;
  irr::scene::IAnimatedMeshSceneNode			*_node;
  bool							explode_box(size_t x, size_t y);

 public:
  Bomb(BoxType::eBoxType type, Position pos, size_t range, Map &map,
       ACharacter &owner, SoundManager *sound_manager, MeshesLoader *mesh, ImagesLoader *img);
  Bomb(const Bomb &other);
  Bomb							&operator=(const Bomb &other);
  virtual void						Check_timer_state();
  virtual void						Explode();
  ACharacter const &					Get_owner() const;
  void							Add_to_timer(std::chrono::milliseconds
								     const &t);
  virtual ~Bomb();
};

#endif /* !BOMB_HH_ */
