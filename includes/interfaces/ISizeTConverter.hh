#ifndef ISIZET_CONVERTER_HH_
# define ISIZET_CONVERTER_HH_

# include <cstddef>
# include <string>

class	ISizeTConverter
{
private:
public:
  virtual size_t		atoi_ranged(const std::string &to_sizet, size_t min, size_t max) = 0;
  virtual size_t		atoi(const std::string &to_sizet, bool &status) const noexcept = 0;
  virtual size_t		atoi(const std::string &to_sizet) const = 0;
  virtual std::string		itoa(size_t to_string) const = 0;
  virtual ~ISizeTConverter() = default;
};

#endif /* !ISIZET_CONVERTER_HH_ */
