#ifndef LEGACY_HH_
# define LEGACY_HH_

# include "ABonus.hh"

class		Legacy final : public ABonus
{
  size_t	_score;
public:
  Legacy(Position pos, Map &map, size_t score, MeshesLoader *mesh, ImagesLoader *img);
  Legacy(const Legacy &other);
  Legacy	&operator=(const Legacy &other);
  virtual void	Apply(ACharacter &character) const;
  virtual ~Legacy() = default;
};

#endif /* !LEGACY_HH_ */
