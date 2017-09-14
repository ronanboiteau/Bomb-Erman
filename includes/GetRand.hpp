#ifndef GETRAND_HPP_
# define GETRAND_HPP_

# include <random>

template<typename T>
class                                   GetRand
{
private:
  std::mt19937                          _randomizer;
  std::uniform_int_distribution<T>	_uniform_tab;
public:
  GetRand() = default;
  GetRand(T min, T max, long seed) :
    _randomizer{std::mt19937(seed)},
    _uniform_tab{std::uniform_int_distribution<T>(min, max)}
  {};
  T	                operator()()
  {
    return (_uniform_tab(_randomizer));
  }
};

#endif /* !GETRAND_HPP_ */
