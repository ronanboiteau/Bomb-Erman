#include "LevelFactory.hh"

LevelFactory::LevelFactory() :
  _levels{
  {L"Easy", eAILevel::EASY},
    {L"Medium", eAILevel::MEDIUM},
      {L"Hard", eAILevel::HARD},
	{L"None", eAILevel::NONE}
}
{
}

eAILevel	LevelFactory::create_level(const std::wstring &level_name) const
{
  return (_levels.at(level_name));
}
