#ifndef HELP_VIEW_EVENT_RECEIVER_HH_
# define HELP_VIEW_EVENT_RECEIVER_HH_

# include "AViewEventReceiver.hh"

class			HelpViewEventReceiver final : public AViewEventReceiver
{
private:
  std::vector<SGuiElem>	&_elements;
public:
  HelpViewEventReceiver(ViewManager *vm);
  bool			OnEvent(const irr::SEvent &event);
  ~HelpViewEventReceiver() = default;
};

#endif /* !HELP_VIEW_EVENT_RECEIVER_HH_ */
