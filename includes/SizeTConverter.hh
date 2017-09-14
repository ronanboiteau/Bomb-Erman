#ifndef SIZET_CONVERTER_HH_
# define SIZET_CONVERTER_HH_

# include "ISizeTConverter.hh"

class	SizeTConverter final : public ISizeTConverter
{
private:
public:
  size_t		atoi_ranged(const std::string &to_sizet, size_t min, size_t max);
  size_t		atoi(const std::string &to_sizet, bool &status) const noexcept;
  size_t		atoi(const std::string &to_sizet) const;
  size_t		atoi(const std::wstring &to_sizet) const;
  std::string		itoa(size_t to_string) const;
  ~SizeTConverter() = default;
};

#endif /* !SIZET_CONVERTER_HH_ */
