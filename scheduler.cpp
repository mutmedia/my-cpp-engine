#include "scheduler.h"

Scheduler::Scheduler() {}

Scheduler::~Scheduler() {}

void Scheduler::Update(SchedulerTime delta_time) {
  current_time_ += delta_time;
  for (auto &kv : scheduled_tasks_) {
    if (kv.first > current_time_) {
      continue;
    }

    for (auto &callback : kv.second) {
      callback();
    }

    // TODO: clear kv.second
    kv.second.clear();
  }
}

void Scheduler::Add(SchedulerTime dt, SchedulerTask task) {
    SchedulerTime schedule_time = current_time_ + dt;
    auto find = scheduled_tasks_.find(schedule_time);
    if(find == scheduled_tasks_.end()) {
        scheduled_tasks_[schedule_time] = SchedulerTaskList();
    }
    scheduled_tasks_[schedule_time].push_back(task);
}