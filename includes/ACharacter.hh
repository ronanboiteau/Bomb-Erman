#ifndef ACHARACTER_HH_
# define ACHARACTER_HH_

# include <string>
# include <cstddef>
# include "Position.hh"
# include "Map.hh"
# include "MeshesLoader.hh"
# include "ImagesLoader.hh"
# include "SoundManager.hh"

class ILikeToMoveIt;

enum class	eHeading : size_t
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

enum class	eColor : size_t
  {
    BLUE = 0,
    RED = 1,
    GREEN = 2,
    ORANGE = 3
  };

class					ACharacter
{
protected:
  std::wstring				_name;
  eColor				_color;
  Map					*_map;
  eHeading				_heading;
  size_t				_id;
  bool					_extra_life;
  size_t				_range_bomb;
  size_t				_sim_bomb;
  size_t				_score;
  bool					_has_master_bomb;

  bool					check_move(eHeading action);

  // ITriangleSelector			*_selector;
  irr::scene::IAnimatedMesh		*_mesh;
  irr::scene::IAnimatedMeshSceneNode	*_node;
  bool					_is_AI;
  Position				_pos;
  int					_is_moving;
  bool					_am_i_dead;
  size_t				_active_bombs;
  SoundManager				*_sound;
  std::vector<ACharacter *> *		_characters;
  MeshesLoader				*_meshesLoader;
  ImagesLoader				*_imagesLoader;
  
public:
  ACharacter(const std::wstring &name, eColor color, Position pos, Map &map, eHeading heading, size_t id, SoundManager *sound, bool is_AI, MeshesLoader *meshesLoader, ImagesLoader *imagesloder);
  ACharacter(const std::wstring &file_to_load);
  ACharacter(const ACharacter &character);
  ACharacter		&operator=(const ACharacter &character);
  std::wstring const	&Get_name() const;
  eColor		Get_color() const;
  size_t		Get_id() const;
  eHeading		Get_heading() const;
  bool			Has_extra_life() const;
  size_t		Get_range_bomb() const;
  size_t		Get_sim_bomb() const;
  size_t		Get_score() const;
  irr::scene::IAnimatedMeshSceneNode	*Get_node();  
  bool			Is_AI() const;
  Position		Get_pos() const;
  bool			Has_master_bomb() const;
  void			Set_name(const std::wstring &name);
  void			Set_color(eColor color);
  void			Set_extra_life(bool extra_life);
  void			Inc_range_bomb();
  void			Inc_sim_bomb();
  void			Add_score(size_t score);
  void			Set_master_bomb(bool has_master_bomb);
  bool			Move(eHeading action);
  void                  SetPosition(int x, int y, int z);
  void                  SetRotation(eHeading h);
  void			Drop_bomb();
  void			Decrement_active_bombs();
  virtual void		Set_heading(ILikeToMoveIt const &receiver) = 0;
  void			Spawn();
  void			Take_bonus(const Position &pos);
  void			Take_bonus();
  bool			Am_i_dead() const;
  void			Set_am_i_dead(bool am_i_dead);
  void			Set_characters(std::vector<ACharacter *> &characters);
  void			Kill_it();
  int			Get_is_moving() const;
  virtual ~ACharacter();
};

#endif /* !ACHARACTER_HH_ */
