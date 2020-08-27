#include "processor.h"
#include <string>
#include "linux_parser.h"
#include <iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

    float totald, idled; //local
   
    // Read in total and idle usage
    cpuUsageTotal_ = LinuxParser::Jiffies();                    
    cpuUsageIdle_ = LinuxParser::IdleJiffies();     
    
    // calculate change
    totald = cpuUsageTotal_ - cpuUsageTotalLast_;
    idled = cpuUsageIdle_ - cpuUsageIdleLast_;
    
    // Save measurements
    cpuUsageTotalLast_ = cpuUsageTotal_;
    cpuUsageIdleLast_ = cpuUsageIdle_;
    
    return ( ( totald - idled ) / totald );
    }