#ifndef UNBREAKABLE_HH_
# define UNBREAKABLE_HH_

# include "ABox.hh"

class	Unbreakable final : public ABox
{
public:
  Unbreakable(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  Unbreakable(const Unbreakable &other);
  Unbreakable	&operator=(const Unbreakable &other);
  virtual ~Unbreakable();

  irr::scene::IMeshSceneNode const &    Get_mesh() const;
 private:
  irr::scene::IMeshSceneNode*	_mesh;
};

#endif /* !UNBREAKABLE_HH_ */
