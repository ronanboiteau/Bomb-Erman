#ifndef AI_HH_
# define AI_HH_

# include <map>
# include "ACharacter.hh"

enum class	eAILevel : size_t
  {
    EASY = 0,
    MEDIUM = 1,
    HARD = 2,
    NONE = 3
  };

struct		sWay {
  int		_count;
  eHeading	_heading;
  int		_danger;
  size_t	_goal;
  size_t	_collision;

  sWay(size_t count, eHeading heading) :
    _count(count),
    _heading(heading),
    _danger(0),
    _goal(0)
  {};
  sWay() :
    _count(-1),
    _danger(0),
    _goal(0)
  {};

  sWay	operator=(const sWay &other)
  {
    this->_count = other._count;
    this->_heading = other._heading;
    this->_danger = other._danger;
    this->_goal = other._goal;
    this->_collision = other._collision;
    return (*this);
  }

  bool	operator==(const sWay &other)
  {
    return (this->_count == other._count && this->_heading == other._heading);
  }
  
  bool	operator!=(const sWay &other)
  {
    return (this->_count != other._count || this->_heading != other._heading);
  }
};

class		AI final : public ACharacter
{
  eAILevel				_level;
public:
  AI(const std::wstring &name, eColor color, Position pos, Map &map,
     eHeading heading, size_t id, eAILevel level, SoundManager *sound, MeshesLoader *meshesLoader, ImagesLoader *imagesLoader);

  AI(const std::wstring &file_to_load);
  virtual void				Set_heading(ILikeToMoveIt const &receiver);

  void					Set_characters(std::vector<ACharacter *> &characters);
  eAILevel				Get_level() const;
  bool					Get_is_visible() const;
  void					Set_is_visible();
  
 private:
  void					_print_debug() const;
  void					_expand(int x, int y, int range, int hey);
  void					_find_safe_zone();
  bool					_find_goal();
  int					_is_danger(Position const &pos) const;
  bool					_is_collision(Position const &pos) const;
  bool					_is_goal(Position const &pos) const;
  void					_set_danger_zone();
  void					_set_collision();
  void					_set_goal(size_t x, size_t y);
  void					_recursive_feelings(size_t x, size_t y,
						  int count, eHeading heading);
  void					_set_way();
  std::vector<std::vector<bool> >	_collision;
  std::vector<std::vector<sWay> >	_way;
  
  void					_easy_script();
  void					_medium_script();
  void					_hard_script();
  std::map<eAILevel, void (AI::*)()>	_script_level = {
    { eAILevel::EASY, &AI::_easy_script },
    { eAILevel::MEDIUM, &AI::_medium_script },
    { eAILevel::HARD, &AI::_hard_script }
  };
};

#endif /* !AI_HH_ */
