#ifndef BREAKABLE_HH_
# define BREAKABLE_HH_

# include "ABox.hh"

class	Breakable final : public ABox
{
public:
  Breakable(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  Breakable(const Breakable &other);
  Breakable	&operator=(const Breakable &other);
  virtual ~Breakable();

  irr::scene::IMeshSceneNode const &	Get_mesh() const;

 private:
  irr::scene::IMeshSceneNode*	_mesh;
};

#endif /* !BREAKABLE_HH_ */
