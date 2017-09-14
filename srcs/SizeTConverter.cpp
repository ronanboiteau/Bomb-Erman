#include <climits>
#include <sstream>
#include "SizeTConverter.hh"
#include "SizeTConverterException.hh"

/*
  Une implémentation imparfaite qui se base sur le fait que les chiffres sont à la suite
  dans l'implémentation des caractères ASCII et qu'un unsigned long long >= SIZE_MAX
*/

size_t		SizeTConverter::atoi(const std::string &to_sizet, bool &status) const noexcept
{
  size_t	ret{0};
  status = false;
  for (size_t idx = 0; idx < to_sizet.size(); ++idx)
    {
      if (to_sizet[idx] < '0' || to_sizet[idx] > '9')
	return (ret);
      if (static_cast<unsigned long long>((ret * 10) + (to_sizet[idx] - '0')) > static_cast<unsigned long long>(SIZE_MAX))
	return (ret);
      ret = (ret * 10) + (to_sizet[idx] - '0');
    }
  status = true;
  return (ret);
}

size_t		SizeTConverter::atoi_ranged(const std::string &to_sizet, size_t min, size_t max)
{
  size_t	value{SizeTConverter::atoi(to_sizet)};

  if (value < min
      || value > max)
    throw SizeTConverterException("Conversion out of range specify");
  return (value);
}

size_t		SizeTConverter::atoi(const std::string &to_sizet) const
{
  size_t	ret{0};
  for (size_t idx = 0; idx < to_sizet.size(); ++idx)
    {
      if (to_sizet[idx] < '0' || to_sizet[idx] > '9')
	{
	  std::stringstream	error_str;
	  error_str << "Conversion error, '" << to_sizet[idx] << "', at position [" << idx << "] isn't a valid char" << std::endl;
	  throw SizeTConverterException(error_str.str());
	}
      if (static_cast<unsigned long long>((ret * 10) + (to_sizet[idx] - '0')) > static_cast<unsigned long long>(SIZE_MAX))
	throw SizeTConverterException("Conversion error, overflow detected");
      ret = (ret * 10) + (to_sizet[idx] - '0');
    }
  return (ret);
}

std::string		SizeTConverter::itoa(size_t to_string) const
{
  std::string		ret;
  char			letter;
  size_t		ten_multiple{1};
  while ((to_string / ten_multiple) >= 10)
    ten_multiple *= 10;
  while (ten_multiple >= 1)
    {
      letter = (((to_string / ten_multiple) % 10) + '0');
      ret += letter;
      ten_multiple /= 10;
    }
  return (ret);
}
