#ifndef EMPTY_HH_
# define EMPTY_HH_

# include "ABox.hh"

class	Empty final : public ABox
{
public:
  Empty(Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  Empty(const Empty &other);
  Empty		&operator=(const Empty &other);
  ~Empty() = default;
};

#endif /* !EMPTY_HH_ */
