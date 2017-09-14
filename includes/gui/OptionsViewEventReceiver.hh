#ifndef OPTIONS_VIEW_EVENT_RECEIVER_HH_
# define OPTIONS_VIEW_EVENT_RECEIVER_HH_

# include "OptionsManager.hh"
# include "AViewEventReceiver.hh"

class			OptionsViewEventReceiver final : public AViewEventReceiver
{
private:
  OptionsManager	*_options_manager;
  std::vector<SGuiElem>	&_elements;
public:
  OptionsViewEventReceiver(ViewManager *vm, OptionsManager *om);
  bool			OnEvent(const irr::SEvent &event);
  ~OptionsViewEventReceiver() = default;
};

#endif /* !OPTIONS_VIEW_EVENT_RECEIVER_HH_ */
