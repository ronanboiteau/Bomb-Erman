#include "ColorFactory.hh"

ColorFactory::ColorFactory() :
  _colors{
  {L"Blue", eColor::BLUE},
    {L"Red", eColor::RED},
      {L"Green", eColor::GREEN},
	{L"Orange", eColor::ORANGE}
}
{
}

eColor	ColorFactory::create_color(const std::wstring &color_name) const
{
  return (_colors.at(color_name));
}
