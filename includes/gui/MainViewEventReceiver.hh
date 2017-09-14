#ifndef MAIN_VIEW_EVENT_RECEIVER_HH_
# define MAIN_VIEW_EVENT_RECEIVER_HH_

# include "AViewEventReceiver.hh"

class	MainViewEventReceiver : public AViewEventReceiver
{
private:
  bool	&_stop;
public:
  MainViewEventReceiver(ViewManager *vm,
			bool &stop);
  bool	OnEvent(const irr::SEvent &event);
  ~MainViewEventReceiver() = default;
};

#endif /* !MAIN_VIEW_EVENT_RECEIVER_HH_ */
