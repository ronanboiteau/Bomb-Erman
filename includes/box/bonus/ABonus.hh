#ifndef ABONUS_HH_
# define ABONUS_HH_

# include "ABox.hh"
# include "ACharacter.hh"

class	ABonus : public ABox
{
protected:
  ABonus(BoxType::eBoxType type, Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  ABonus(const ABonus &other);
  irr::scene::IMeshSceneNode	*_meshi;

public:
  ABonus	&operator=(const ABonus &other);
  virtual void	Apply(ACharacter &character) const = 0;
  void		Rotate();
  virtual ~ABonus();
};

#endif /* !ABONUS_HH_ */
