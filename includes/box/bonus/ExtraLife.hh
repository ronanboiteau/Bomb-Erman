#ifndef EXTRALIFE_HH_
# define EXTRALIFE_HH_

# include "ABonus.hh"

class		ExtraLife final : public ABonus
{
public:
  ExtraLife(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  ExtraLife(const ExtraLife &other);
  ExtraLife	&operator=(const ExtraLife &other);
  virtual void	Apply(ACharacter &character) const;
  virtual ~ExtraLife() = default;
};

#endif /* !EXTRALIFE_HH_ */
