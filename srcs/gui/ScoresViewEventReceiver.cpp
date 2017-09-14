#include <sstream>
#include <SizeTConverter.hh>
#include "ViewsInstantiator.hh"
#include "ScoresViewEventReceiver.hh"
#include "ScoresViewEventReceiverException.hh"

ScoresViewEventReceiver::ScoresViewEventReceiver(ViewManager *vm) :
  AViewEventReceiver{vm},
  _elements{vm->Get_elems_for_view(ViewID::HIGHSCORES)}
{
}

bool	ScoresViewEventReceiver::OnEvent(const irr::SEvent &event)
{
  if (!(event.EventType == irr::EEVENT_TYPE::EET_LOG_TEXT_EVENT
	|| (event.EventType == irr::EEVENT_TYPE::EET_GUI_EVENT
	    && event.GUIEvent.EventType == irr::gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED)))
    return (false);
  if (event.EventType == irr::EEVENT_TYPE::EET_LOG_TEXT_EVENT)
    {
      std::string	log_str{event.LogEvent.Text};
      std::string	prefix{"score_up: "};
      std::string	player_name;
      if (log_str.size() < prefix.size()
	  || log_str.substr(0, prefix.size()) != prefix)
	return (false);
      std::stringstream	logs_stream{log_str.substr(prefix.size(), log_str.size() - prefix.size())};
      SizeTConverter	converter;
      std::string	player_score_str;
      size_t		player_score;
      size_t		nb_player;
      size_t		y_pos{28};

      std::getline(logs_stream, player_name);
      if (!logs_stream.good())
	throw ScoresViewEventReceiverException("invalid nb_player");
      nb_player = converter.atoi(player_name);
      for (size_t idx = 0; idx < nb_player * 2; idx += 2)
	{
	  std::getline(logs_stream, player_name);
	  if (!logs_stream.good())
	    throw ScoresViewEventReceiverException("Invalid score player name log");
	  std::getline(logs_stream,player_score_str);
	  if (!logs_stream.good())
	    throw ScoresViewEventReceiverException("Invalid score player score");
	  player_score = converter.atoi(player_score_str);
	  _elements[idx + 1]._StaticTextParams._text = new std::wstring(player_name.begin(), player_name.end());
	  _elements[idx + 1]._distance_from_left_border = 30;
	  _elements[idx + 1]._distance_from_top_border = y_pos;
	  _elements[idx + 2]._StaticTextParams._text = new std::wstring(player_score_str.begin(), player_score_str.end());
	  _elements[idx + 2]._distance_from_left_border = 60;
	  _elements[idx + 2]._distance_from_top_border = y_pos;
	  y_pos += 10;
	}
      return (true);
    }
  switch (static_cast<ButtonsID::Scores>(event.GUIEvent.Caller->getID()))
    {
    case ButtonsID::Scores::RETURN:
      _view_manager->Set_view(ViewID::MAIN_MENU);
      return (true);
    }
  return (false);
}
