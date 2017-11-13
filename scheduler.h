#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <functional>
#include <map>
#include <vector>

typedef float SchedulerTime;
typedef std::function<void()> SchedulerTask;
typedef std::vector<SchedulerTask> SchedulerTaskList;

struct SheduledTask {
  SchedulerTask task;
};

class Scheduler {
public:
  Scheduler();
  ~Scheduler();
  void Update(SchedulerTime delta_time);
  void Add(SchedulerTime dt, SchedulerTask task);

private:
  // TODO: implement this with heap (performance)
  std::map<SchedulerTime, SchedulerTaskList> scheduled_tasks_;
  SchedulerTime current_time_;
};

#endif