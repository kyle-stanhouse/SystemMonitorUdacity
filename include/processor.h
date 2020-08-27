#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <string>

class Processor {
 public:
  float Utilization();  // DONE: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
    long cpuUsageTotal_ = 0;
    long cpuUsageTotalLast_ = 0;
    long cpuUsageIdle_ = 0;
    long cpuUsageIdleLast_ = 0;
};

#endif