#ifndef MULTIPLE_VALIDATOR_HPP_
# define MULTIPLE_VALIDATOR_HPP_

# include <cstddef>
# include <iostream>

template <typename T>
class	MultipleValidator
{
private:
  T	_base;
  T	_multiple_minimum;
  T	_multiple_maximum;
  T	_multiple_bonus_max_allowed;
  T	_base_to_ret;
public:
  MultipleValidator(T base,
		    T multiple_minimum,
		    T multiple_maximum,
		    T multiple_bonus_max_allowed) :
    _base{base},
    _multiple_minimum{multiple_minimum},
    _multiple_maximum{multiple_maximum},
    _multiple_bonus_max_allowed{multiple_bonus_max_allowed}
  {
  }
  bool		operator()(T to_test)
  {
    T	min{_multiple_minimum};

    while (min <= _multiple_maximum)
      {
	if (to_test >= (min * _base)
	    && to_test <= ((min * _base) + _multiple_bonus_max_allowed))
	  {
	    _base_to_ret = (min * _base);
	    return (true);
	  }
	++min;
      }
    _base_to_ret = 0;
    return (false);
  }
  T		Get_base() const
  {
    return (_base_to_ret);
  }
  ~MultipleValidator() = default;
};

#endif /* !MULTIPLE_VALIDATOR_HPP_ */
