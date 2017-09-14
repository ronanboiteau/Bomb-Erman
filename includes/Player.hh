#ifndef PLAYER_HH_
# define PLAYER_HH_

# include "ACharacter.hh"

class		Player final : public ACharacter
{
public:
  Player(const std::wstring &name, eColor color, Position pos, Map &map, eHeading heading, size_t id, SoundManager *sound, MeshesLoader *meshesLoader, ImagesLoader *imagesLoader);
  Player(const std::wstring &file_to_load);
  virtual void		Set_heading(ILikeToMoveIt const &receiver);
 private:
  std::vector<irr::EKEY_CODE>	_key;
};

#endif /* !PLAYER_HH_ */
