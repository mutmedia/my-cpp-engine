#include "events.h"

#include <algorithm>

EventSystem::EventSystem() {
    permanent_events.clear();
}

EventSystem::~EventSystem() {

}

void EventSystem::add_new(Event e, Callback c, EventRecurrence r) {
    if(r == EVENT_PERMANENT) {
        auto find = permanent_events.find(e);
        if(find == permanent_events.end()) {
            permanent_events[e] = CallbackList();
        }
        permanent_events[e].push_back(c);
    }
}

void EventSystem::add(Event e, Callback c) {
    add_new(e, c, EVENT_PERMANENT);
}

void EventSystem::fire(Event e) {
    auto find = permanent_events.find(e);
    if(find == permanent_events.end()) return;
    std::for_each(
        permanent_events[e].begin(), 
        permanent_events[e].end(), 
        [](Callback c) { c(); }
    );
}
