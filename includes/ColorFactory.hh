#ifndef COLOR_FACTORY_HH_
# define COLOR_FACTORY_HH_

# include <string>
# include <unordered_map>
# include "ACharacter.hh"

class	ColorFactory final
{
private:
  std::unordered_map<std::wstring, eColor>	_colors;
public:
  ColorFactory();
  eColor	create_color(const std::wstring &color_name) const;
  ~ColorFactory() = default;
};

#endif /* !COLOR_FACTORY_HH_ */
