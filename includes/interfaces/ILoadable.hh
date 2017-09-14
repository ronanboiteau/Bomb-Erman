#ifndef ILOADABLE_HH_
# define ILOADABLE_HH_

# include <string>

class	ILoadable
{
private:
public:
  virtual void	Load(const std::string &filepath) = 0;
  virtual ~ILoadable() = default;
};

#endif /* !ILOADABLE_HH_ */
