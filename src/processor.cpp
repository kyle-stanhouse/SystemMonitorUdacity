#include "processor.h"
#include <string>
#include "linux_parser.h"
#include <iostream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 

    float totald, idled; //local, perhaps unneccesary

    //std::vector<std::string> cpuJiffies_ = LinuxParser::CpuUtilization(); //local 
    cpuJiffies_ = LinuxParser::CpuUtilization();
    
    //cpu_util_total = std::stof(user) + std::stof(nice) + std::stof(system) + std::stof(idle) + std::stof(iowait) + std::stof(irq) + std::stof(softirq) + std::stof(steal) + std::stof(guest) + std::stof(guest_nice); 
    //cpuUsageTotal_ = std::stof(cpuJiffies_[0]) + std::stof(cpuJiffies_[1]) + std::stof(cpuJiffies_[2]) + std::stof(cpuJiffies_[3]) + std::stof(cpuJiffies_[4]) + std::stof(cpuJiffies_[5]) + std::stof(cpuJiffies_[6]) + std::stof(cpuJiffies_[7]) + std::stof(cpuJiffies_[8]) + std::stof(cpuJiffies_[9]); 
    cpuUsageTotal_ = std::stof(cpuJiffies_[0]) + std::stof(cpuJiffies_[1]) + std::stof(cpuJiffies_[2]) + 
                        std::stof(cpuJiffies_[LinuxParser::kIdle_]) + std::stof(cpuJiffies_[LinuxParser::kIOwait_]) + 
                            std::stof(cpuJiffies_[5]) + std::stof(cpuJiffies_[6]) + std::stof(cpuJiffies_[7]) + 
                                std::stof(cpuJiffies_[8]) + std::stof(cpuJiffies_[9]); 
        
    cpuUsageIdle_ = std::stof(cpuJiffies_[LinuxParser::kIdle_]) + std::stof(cpuJiffies_[LinuxParser::kIOwait_]);     
    totald = cpuUsageTotal_ - cpuUsageTotalLast_;
    idled = cpuUsageIdle_ - cpuUsageIdleLast_;

    //std::cout << LinuxParser::CPUStates(0) << std::endl;
    int test = LinuxParser::CPUStates(4);
    
    // Save measurements 
    //cpuJiffiesLast_ = cpuJiffies_;
    cpuUsageTotalLast_ = cpuUsageTotal_;
    cpuUsageIdleLast_ = cpuUsageIdle_;
            
    //activeJiffies_ = LinuxParser::ActiveJiffies(cpuJiffies_);
    //idleJiffies_ = LinuxParser::IdleJiffies(cpuJiffies_);
    //totalJiffies_ = LinuxParser::Jiffies(cpuJiffies_);
    
    return ( ( totald - idled ) / totald );
    }