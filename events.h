#ifndef EVENTS_H
#define EVENTS_H

#define EVENT_ONCE 0
#define EVENT_PERMANENT 1

#include <functional>
#include <map>
#include <vector>

typedef char Event;
typedef char EventRecurrence;
typedef std::function<void()> Callback;
typedef std::vector<Callback> CallbackList;

class EventSystem {
public:
    EventSystem();
    ~EventSystem();
    void add(Event e, Callback callback);
    //void schedule(Event e, Callback callback);
    //void countdown(Event e, int count, Callback callback)
    void fire(Event e);
private:
    void add_new(Event e, Callback callback, EventRecurrence recurrence); 
    std::map<Event, CallbackList> permanent_events;
};

#endif