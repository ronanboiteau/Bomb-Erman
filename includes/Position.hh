#ifndef POSITION_HH_
# define POSITION_HH_

# include <cstddef>

struct		Position
{
  size_t	_x;
  size_t	_y;
  Position() {};
  bool		operator==(const Position &other)
  {
    return (this->_x == other._x && this->_y == other._y);
  }
  bool		operator!=(const Position &other)
  {
    return (this->_x != other._x || this->_y != other._y);
  }
  Position(size_t x, size_t y) :
    _x(x),
    _y(y)
  {};
};

#endif /* !POSITION_HH_ */
