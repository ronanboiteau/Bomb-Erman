#ifndef MULTIPLE_EVENT_RECEIVER_HH_
# define MULTIPLE_EVENT_RECEIVER_HH_

# include <list>
# include "IMultipleEventReceiver.hh"
# include "ViewManager.hh"
# include "RessourcesLoader.hh"
# include "MainViewEventReceiver.hh"
# include "OptionsViewEventReceiver.hh"
# include "GameParametersViewEventReceiver.hh"
# include "ScoresViewEventReceiver.hh"
# include "HelpViewEventReceiver.hh"
# include "SavesViewEventReceiver.hh"
# include "SaveInformation.hh"

class	MultipleEventReceiver final : public IMultipleEventReceiver
{
private:
  std::list<irr::IEventReceiver*>	_events_receivers;
  ViewManager				*_view_manager;
  MainViewEventReceiver			_main_ve_receiver;
  OptionsViewEventReceiver		_options_ve_receiver;
  GameParametersViewEventReceiver	_game_params_ve_receiver;
  ScoresViewEventReceiver		_scores_ve_receiver;
  HelpViewEventReceiver			_help_ve_receiver;
  SavesViewEventReceiver		_saves_ve_receiver;
public:
  MultipleEventReceiver(ViewManager *view_manager,
			OptionsManager *settings,
			GameParameters *game_parameters,
			bool &stop,
			SaveInformation &save);
  bool	OnEvent(const irr::SEvent &event);
  void	Add_new_event_receiver(irr::IEventReceiver *new_event_receiver);

  ~MultipleEventReceiver() = default;
};

#endif /* MULTIPLE_EVENT_RECEIVER_HH_ */
