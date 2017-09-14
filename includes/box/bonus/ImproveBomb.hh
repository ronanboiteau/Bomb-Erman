#ifndef IMPROVEBOMB_HH_
# define IMPROVEBOMB_HH_

# include "ABonus.hh"

class		ImproveBomb final : public ABonus
{
public:
  ImproveBomb(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  ImproveBomb(const ImproveBomb &other);
  ImproveBomb	&operator=(const ImproveBomb &other);
  virtual void	Apply(ACharacter &character) const;
  virtual ~ImproveBomb() = default;
};

#endif /* !IMPROVEBOMB_HH_ */
