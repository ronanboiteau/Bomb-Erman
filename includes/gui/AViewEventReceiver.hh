#ifndef AVIEW_EVENT_RECEIVER_HH_
# define AVIEW_EVENT_RECEIVER_HH_

# include <irrlicht.h>
# include "ViewManager.hh"

class	AViewEventReceiver : public irr::IEventReceiver
{
protected:
  ViewManager	*_view_manager;
public:
  AViewEventReceiver(ViewManager *vm) :
    _view_manager{vm}
  {
  };
  virtual ~AViewEventReceiver() = default;
};

#endif /* !AVIEW_EVENT_RECEIVER_HH_ */
