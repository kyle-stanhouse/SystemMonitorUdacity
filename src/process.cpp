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

// DONE: Return this process's ID
int Process::Pid() { 

    return pid_; //Accessor
    }

// DONE: Return this process's CPU utilization
// called in ncurses_display.cpp
float Process::CpuUtilization() { 
    
    //long LinuxParser::ActiveJiffies(int pid_);
    //cpuUtil_ = LinuxParser::ActiveJiffies(pid_); 
    //return cpuUtil_;
    return LinuxParser::ActiveJiffies(pid_);
    }
    
void Process::setCPU(){

    cpuUtil_ = LinuxParser::ActiveJiffies(pid_);
}
void Process::setRAM(){

    ram_ = LinuxParser::Ram(pid_);
}

// DONE: Return the command that generated this process
string Process::Command() { 
    
    //std::string Command(int pid);
    return LinuxParser::Command(pid_);
    }

// DONE: Return this process's memory utilization
string Process::Ram() { 
    
    //std::string Ram(int pid);
    return LinuxParser::Ram(pid_); 
    }

// DONE: Return the user (name) that generated this process
string Process::User() { 
    
    //LinuxParser::User(int pid) // LinuxParser::Uid is called by User
    return LinuxParser::User(pid_); 
    }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { 
    
    //long int UpTime(int pid);
    return LinuxParser::UpTime(pid_); 
    }

// DONE: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const { 
    
   
   //return ( std::stoi(ram_) < std::stoi(a.ram_) ); //sort by ram
   return ( cpuUtil_ < a.cpuUtil_);
}