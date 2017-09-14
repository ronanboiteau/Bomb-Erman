#ifndef SCORES_VIEW_EVENT_RECEIVER_HH_
# define SCORES_VIEW_EVENT_RECEIVER_HH_

# include "AViewEventReceiver.hh"

class	ScoresViewEventReceiver final : public AViewEventReceiver
{
private:
  std::vector<SGuiElem>	&_elements;
public:
  ScoresViewEventReceiver(ViewManager *vm);
  bool		OnEvent(const irr::SEvent &event);
  ~ScoresViewEventReceiver() = default;
};

#endif /* !SCORES_VIEW_EVENT_RECEIVER_HH_ */
