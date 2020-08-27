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

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a[[maybe_unused]]) const { 
bool Process::operator<(Process const& a) const { 
    
    bool less_than; 
    // if cpuUtil_ is less than a.cpuUtil return a, else if vice versa return b, if a==b, it returns b
    //return cpuUtil_ > a.cpuUtil_ ? cpuUtil_ : a.cpuUtil_;
    /*
    if (cpuUtil_ < a.cpuUtil_){
        less_than = true;
    }
    else if(a.cpuUtil_ > cpuUtil_){
        less_than = false;
    }
    else if(cpuUtil_ == a.cpuUtil_){
        less_than = true;
    }
    */
    
    //return ram_ > a.ram_ ? ram_ : a.ram_;
    ///*
    if (ram_ < a.ram_){
        less_than = true;
    }
    else if(a.ram_ > ram_){
        less_than = false;
    }
    else if(ram_ == a.ram_){
        less_than = true;
    }
    //*/
   return less_than;  
}