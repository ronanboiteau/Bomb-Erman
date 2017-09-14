#ifndef UPRANGE_HH_
# define UPRANGE_HH_

# include "ABonus.hh"

class		UpRange final : public ABonus
{
public:
  UpRange(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  UpRange(const UpRange &other);
  UpRange	&operator=(const UpRange &other);
  virtual void	Apply(ACharacter &character) const;
  virtual ~UpRange() = default;
};

#endif /* !UPRANGE_HH_ */
