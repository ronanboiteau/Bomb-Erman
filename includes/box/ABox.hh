#ifndef ABOX_HH_
# define ABOX_HH_

# include <irrlicht.h>
# include "MeshesLoader.hh"
# include "ImagesLoader.hh"
# include "BoxType.hh"
# include "Map.hh"
# include "Position.hh"

class Map;

class	ABox
{
private:
  BoxType::eBoxType	_type;
  Position	_pos;

protected:
  MeshesLoader	*_mesh;
  ImagesLoader	*_img;
  ABox(BoxType::eBoxType type, Position pos, Map &map, MeshesLoader *mesh, ImagesLoader *img);
  ABox(ABox const &other);
  Map		*_map;

public:
  ABox		&operator=(const ABox &other);
  Position	Get_pos() const;
  BoxType::eBoxType	Get_type() const;
  bool		Is_a_block() const;
  bool		Is_a_bomb() const;
  bool		Is_a_bonus() const;
  bool		Is_destroyable() const;
  void		Set_pos(const Position &pos);
  void		Set_type(BoxType::eBoxType type);
  virtual ~ABox() = default;
};

#endif /* !ABOX_HH_ */
