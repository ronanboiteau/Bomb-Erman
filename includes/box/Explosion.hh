#ifndef EXPLOSION_HH_
# define EXPLOSION_HH_

# include <chrono>
# include "ABox.hh"
# include "Map.hh"

class	Explosion final : public ABox
{
private:
  bool		_can_into_bonus;
  std::chrono::time_point<std::chrono::system_clock>	_time_created;
  void		end_of_explosion();
  void		put_bonus();
  irr::scene::IBillboardSceneNode *	_meshi;

public:
  Explosion(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  Explosion(const Explosion &other);
  Explosion	&operator=(const Explosion &other);
  void		Check_timer_state();
  void		Set_can_into_bonus(bool can_into_bonus);
  irr::scene::IBillboardSceneNode const&    Get_mesh() const;
  void	Set_mesh(irr::scene::IBillboardSceneNode const &mesh);
  void	Add_to_timer(std::chrono::milliseconds const &t);
  virtual ~Explosion();
};

#endif /* !EXPLOSION_HH_ */
