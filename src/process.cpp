#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { 

    return pid_; //Accessor
    }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    
    //long LinuxParser::ActiveJiffies(int pid_);

    return LinuxParser::ActiveJiffies(pid_); 
    }

// TODO: Return the command that generated this process
string Process::Command() { 
    
    //std::string Command(int pid);
    //return string(); 
    return LinuxParser::Command(pid_);
    }

// TODO: Return this process's memory utilization
string Process::Ram() { 
    
    //std::string Ram(int pid);
    return LinuxParser::Ram(pid_); 
    }

// TODO: Return the user (name) that generated this process
string Process::User() { 
    
    //std::string Uid(int pid);
    //LinuxParser::User(int pid) // LinuxParser::Uid is called by User
    return LinuxParser::User(pid_); 
    }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    
    //long int UpTime(int pid);
    return LinuxParser::UpTime(pid_); 
    }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { 
    
    
    return true; 
    }