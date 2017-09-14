#include "MultipleEventReceiver.hh"

MultipleEventReceiver::MultipleEventReceiver(ViewManager *view_manager,
					     OptionsManager *settings,
					     GameParameters *game_parameters,
					     bool &stop,
					     SaveInformation &save) :
  _view_manager{view_manager},
  _main_ve_receiver{_view_manager, stop},
  _options_ve_receiver{_view_manager, settings},
  _game_params_ve_receiver{_view_manager, game_parameters},
  _scores_ve_receiver{_view_manager},
  _help_ve_receiver{_view_manager},
  _saves_ve_receiver{_view_manager, save}
{
  _events_receivers.push_back(&_main_ve_receiver);
  _events_receivers.push_back(&_options_ve_receiver);
  _events_receivers.push_back(&_game_params_ve_receiver);
  _events_receivers.push_back(&_scores_ve_receiver);
  _events_receivers.push_back(&_help_ve_receiver);
  _events_receivers.push_back(&_saves_ve_receiver);
}

bool		MultipleEventReceiver::OnEvent(const irr::SEvent &event)
{
  for (auto & it : _events_receivers)
    {
      if (it->OnEvent(event))
	return (true);
    }
  return (false);
}

void		MultipleEventReceiver::Add_new_event_receiver(irr::IEventReceiver *new_event_receiver)
{
  if (new_event_receiver == nullptr)
    return ;
  _events_receivers.push_back(new_event_receiver);
}
