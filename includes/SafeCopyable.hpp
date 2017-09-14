#ifndef SAFE_COPYABLE_HH_
# define SAFE_COPYABLE_HH_

# include <mutex>
# include "ISafeCopyable.hpp"

template <typename T>
class	SafeCopyable final : public ISafeCopyable<T>
{
private:
  T		_value;
  std::mutex	_the_value_mutex;
public:
  SafeCopyable(T original_value) :
    _value{original_value}{};
  T	Read_safely_value()
  {
    std::unique_lock<std::mutex>	lock{_the_value_mutex};
    return (_value);
  }
  void	Set_safely_value(T new_value)
  {
    std::unique_lock<std::mutex>	lock{_the_value_mutex};
    _value = new_value;
  }
  ~SafeCopyable() = default;
};

#endif /* !SAFE_COPYABLE_HPP_ */
