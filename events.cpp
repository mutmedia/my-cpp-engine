#include "events.h"

#include <algorithm>

EventSystem::EventSystem() {
    permanent_events_.clear();
}

EventSystem::~EventSystem() {

}

void EventSystem::AddNew(Event e, Callback c, EventRecurrence r) {
    if(r == EVENT_PERMANENT) {
        auto find = permanent_events_.find(e);
        if(find == permanent_events_.end()) {
            permanent_events_[e] = CallbackList();
        }
        permanent_events_[e].push_back(c);
    }
}

void EventSystem::Add(Event e, Callback c) {
    AddNew(e, c, EVENT_PERMANENT);
}

void EventSystem::Fire(Event e) {
    auto find = permanent_events_.find(e);
    if(find == permanent_events_.end()) return;
    std::for_each(
        permanent_events_[e].begin(), 
        permanent_events_[e].end(), 
        [](Callback c) { c(); }
    );
}
