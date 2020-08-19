#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line); //allows us to read tokens
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 

  string line, key, value;
  float MemTotal, MemFree, MemAvailable, Buffers, Cached, total, float_value;
  //std::ifstream filestream(kOSPath);
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
            //float_value = std::stof(value);
            MemTotal = std::stof(value);  
          }
        else if( key == "MemFree:"){
            MemFree = std::stof(value); 
        }
        else if( key == "MemAvailable:"){
            MemAvailable = std::stof(value); 
        }
        else if( key == "Buffers:"){
            Buffers = std::stof(value); 
        }
        else if( key == "Cached:"){
            Cached = std::stof(value); 
        }

      }
    }
  }
    //Total used memory = MemTotal - MemFree
    //Non cache/buffer memory (green) = Total used memory - (Buffers + Cached memory)
    //Buffers (blue) = Buffers
    //total = ( (MemTotal - MemFree) - (Buffers + Cached) );
    return ( ( (MemTotal - MemFree) - (Buffers + Cached) ) / MemTotal );
} 

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime, idle;
  string line;
  double uptime_d;
  long int uptime_int;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line); //allows us to read tokens
    linestream >> uptime >> idle;

    //std::cout << uptime << "/n";
    //uptime_d = std::stod(uptime);
    //uptime_int = (int) std::stod(uptime);
  }
  //return (int) std::stod(uptime);
  uptime_int = std::stol(uptime);
  //return std::stol(uptime);
  return uptime_int;
  //return 0;
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  
  //Read and return the number of tokens in the (aggregate) cpu line of '/proc/stat'
  // Total time passed
  /*
  std::string line, key, temp, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  float cpu_util_total;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
      //while (linestream >> key >> kUser_ >> kNice_ >> kSystem_ >> kIdle_ >> kIOwait_ >> kIRQ_ >> kSoftIRQ_ >> kSteal_ >> kGuest_ >> kGuestNice_) {
        //LinuxParser::CPUStates kUser_ = std::stoi(user);
        //LinuxParser::CPUStates kUser_ = 1;
        
        if (key == "cpu") {
            //cpu_util_total = std::stof(kUser_ + kNice_ + kSystem_ + kIdle_ + kIOwait_ + kIRQ_ + kSoftIRQ_ + kSteal_ + kGuest_ + kGuestNice_);  
            cpu_util_total = std::stof(user) + std::stof(nice) + std::stof(system) + std::stof(idle) + std::stof(iowait) + std::stof(irq) + std::stof(softirq) + std::stof(steal) + std::stof(guest) + std::stof(guest_nice); 
            float cpu_usage = ( (cpu_util_total - (std::stof(idle) + std::stof(iowait)) ) / cpu_util_total);
            //break;
            return (int) ( (cpu_util_total - (std::stof(idle) + std::stof(iowait)) ) / cpu_util_total); 
          }
      }
    }
  }
  */
  //return (int) ( (cpu_util_total - (std::stof(idle) + std::stof(iowait)) ) / cpu_util_total); 
  return 0;
  }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  
  // Add the active Jiffies together (kUser_, kNice_, kSystem_, kIRQ_, kSoftIRQ_, kSteal_, kGuest_, kGuestNice_)

  return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  
  // Add the idle Jiffies together (kIdle_, kIOwait_)

  return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  
  //return vector of CPU Jiffies
  //std::string line, key, temp, user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
  std::string line, key, temp;
  vector<std::string> cpuJiffies; //local
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      //while (linestream >> key >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice) {
      while(linestream >> key){
        //word_count++;
        if (key == "cpu") {
            while(linestream >> temp){
              cpuJiffies.push_back(temp);
            }
          }
          break; //exit loop, aggregate cpu stats found
      }
    }
  }
  //return {};
  return cpuJiffies;
  }

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 

  string line, key, value;
  int total_processes;
  //std::ifstream filestream(kOSPath);
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
            total_processes = std::stoi(value);  
            break;
          }
      }
    }
  }
  return total_processes; 
  }

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 

  string line, key, value;
  int running_processes;
  //std::ifstream filestream(kOSPath);
  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
            running_processes = std::stoi(value);  
            break;
          }
      }
    }
  }
  return running_processes; 
  }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }