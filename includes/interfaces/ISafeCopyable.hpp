#ifndef ISAFE_COPYABLE_HPP_
# define ISAFE_COPYABLE_HPP_

template <typename T>
class	ISafeCopyable
{
private:
public:
  virtual T	Read_safely_value() = 0;
  virtual void	Set_safely_value(T value) = 0;
  virtual ~ISafeCopyable() = default;
};

#endif /* !ISAFE_COPYABLE_HPP_ */
