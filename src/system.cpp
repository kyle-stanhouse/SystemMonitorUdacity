#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using namespace LinuxParser;

// General options: 
// Pass through with linux parser methods
// Cache data when system is instantiated or when called by some update function

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    
    // Accessor
    return cpu_; 
    }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
    
    // Read list of Pids using LinuxParser
    std::vector<int> pidFullList = {};
    processes_ = {};
    pidFullList = LinuxParser::Pids();
    //std::vector<int> pidFullList = LinuxParser::Pids();

    // Create Process objects and add to process container
    for ( int i=0; i < (int) pidFullList.size(); i++ ){

        Process process(pidFullList[i]); // create Process objects w/PIDs as input
        processes_.push_back(process); //add to processes_ vector
    }    
   
    // Sort processes according to heaviest use CPU utilization
    // Implementation uses '<' operator overload for processes
    std::sort (processes_.begin(), processes_.end());
    //std::stable_sort (processes_.begin(), processes_.end());
    std::reverse(processes_.begin(), processes_.end());

    return processes_; 
    }

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    
    //Usage: string LinuxParser::Kernel()
    return LinuxParser::Kernel(); 
    }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { 
    
    //float LinuxParser::MemoryUtilization()
    return LinuxParser::MemoryUtilization(); 
    }

// DONE: Return the operating system name
std::string System::OperatingSystem() { 
    
    //Usage: string LinuxParser::OperatingSystem()
    return LinuxParser::OperatingSystem(); 
    }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    
    //Usage: intLinuxParser::RunningProcesses()
    return LinuxParser::RunningProcesses(); 
    }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { 
    
    //Usage: int LinuxParser::TotalProcesses()
    return LinuxParser::TotalProcesses(); 
    }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    
    //Usage: long LinuxParser::UpTime();
    //long int local_int = LinuxParser::UpTime();
    
    return LinuxParser::UpTime(); 
    }