#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <string>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    std::vector<std::string> cpuJiffies_ = {}; // May not be a reason for this to be a persisent attribute
    std::vector<std::string> cpuJiffiesLast_ = {}; // Unused 
    float cpuUsageTotal_ = 0;
    float cpuUsageTotalLast_ = 0;
    float cpuUsageIdle_ = 0;
    float cpuUsageIdleLast_ = 0;
    long activeJiffies_; // Unused 
    long idleJiffies_; // Unused
    long totalJiffies_; // Unused
};

#endif