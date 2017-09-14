#ifndef SIMBOMB_HH_
# define SIMBOMB_HH_

# include "ABonus.hh"

class		SimBomb final : public ABonus
{
public:
  SimBomb(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  SimBomb(const SimBomb &other);
  SimBomb	&operator=(const SimBomb &other);
  virtual void	Apply(ACharacter &character) const;
  virtual ~SimBomb() = default;
};

#endif /* !SIMBOMB_HH_ */
