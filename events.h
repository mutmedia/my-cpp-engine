#ifndef EVENTS_H
#define EVENTS_H

#define EVENT_ONCE 0
#define EVENT_PERMANENT 1

#include <functional>
#include <map>
#include <vector>

typedef int Event;
typedef char EventRecurrence;
typedef std::function<void()> Callback;
typedef std::vector<Callback> CallbackList;

class EventSystem {
public:
  EventSystem();
  ~EventSystem();
  void Add(Event e, Callback callback);
  // void schedule(Event e, Callback callback);
  // void countdown(Event e, int count, Callback callback)
  void Fire(Event e);

private:
  void AddNew(Event e, Callback callback, EventRecurrence recurrence);
  std::map<Event, CallbackList> permanent_events_;
};

#endif
