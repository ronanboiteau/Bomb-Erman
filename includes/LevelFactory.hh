#ifndef LEVEL_FACTORY_HH_
# define LEVEL_FACTORY_HH_

# include <string>
# include <unordered_map>
# include "AI.hh"

class	LevelFactory final
{
private:
  std::unordered_map<std::wstring, eAILevel>	_levels;
public:
  LevelFactory();
  eAILevel	create_level(const std::wstring &level_name) const;
  ~LevelFactory() = default;
};

#endif /* !LEVEL_FACTORY_HH_ */
