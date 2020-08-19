#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <string>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    std::vector<std::string> cpuJiffies_ = {};
    std::vector<std::string> cpuJiffiesLast_ = {};
    float cpuUsageTotal_ = 0;
    float cpuUsageTotalLast_ = 0;
    float cpuUsageIdle_ = 0;
    float cpuUsageIdleLast_ = 0;
    long activeJiffies_;
    long idleJiffies_;
    long totalJiffies_;
};

#endif