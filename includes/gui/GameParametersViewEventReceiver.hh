#ifndef GAME_PARAMETERS_VIEW_EVENT_RECEIVER_HH_
# define GAME_PARAMETERS_VIEW_EVENT_RECEIVER_HH_

# include "GameParameters.hh"
# include "AViewEventReceiver.hh"
# include "MultipleValidator.hpp"
# include "ColorFactory.hh"
# include "LevelFactory.hh"

class		GameParametersViewEventReceiver final : public AViewEventReceiver
{
private:
  GameParameters	*_game_params;
  std::vector<SGuiElem>	&_elements;
  MultipleValidator<size_t>	_is_a_player_gui;
  LevelFactory			_level_factory;
  ColorFactory			_color_factory;
public:
  GameParametersViewEventReceiver(ViewManager *vm, GameParameters *gp);
  bool			OnEvent(const irr::SEvent &event);
  ~GameParametersViewEventReceiver() = default;
};

#endif /* !GAME_PARAMETERS_VIEW_EVENT_RECEIVER_HH_ */
