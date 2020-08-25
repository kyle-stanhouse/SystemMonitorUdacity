#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

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

// BONUS (NOT DONE): Update this to use std::filesystem
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
  float MemTotal, MemFree, Buffers, Cached;
  //float MemAvailable; //unused
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
            MemTotal = std::stof(value);  
          }
        else if( key == "MemFree:"){
            MemFree = std::stof(value); 
        }
        // Ultimately unused  
        //else if( key == "MemAvailable:"){
        //    MemAvailable = std::stof(value); 
        //}
        else if( key == "Buffers:"){
            Buffers = std::stof(value); 
        }
        else if( key == "Cached:"){
            Cached = std::stof(value); 
        }

      }
    }
  }
    return ( ( (MemTotal - MemFree) - (Buffers + Cached) ) / MemTotal );
} 

// DONE: Read and return the system uptime
long LinuxParser::UpTime() { 
  string uptime, idle;
  string line;
  long int uptime_int;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line); //allows us to read tokens
    linestream >> uptime >> idle;

  }
  //return (int) std::stod(uptime);
  uptime_int = std::stol(uptime);
  return uptime_int;
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
long LinuxParser::ActiveJiffies(int pid) { 
  
  string line, token, uptime_str;
  int counter = 1;
  long int utime, stime, cstime, cutime, starttime, total, seconds, Hertz, uptime, cpu_usage;

  //string path = kProcDirectory + to_string(pid) + kStatusFilename;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line); //allows us to read tokens
    //string dummy = linestream[23];
    while(linestream >> token){
      if (counter ==  14){
          utime = std::stol(token);// / sysconf(_SC_CLK_TCK);
          //return std::stol(uptime);
          //return uptime_int;
      }
      else if (counter == 15)
      {
        stime = std::stol(token);
      }
      else if (counter == 16)
      {
        cutime = std::stol(token);
      }
      else if (counter == 17)
      {
        cstime = std::stol(token);
      }
      else if (counter == 22)
      {
        starttime = std::stol(token);
      }
      
      counter++;
    }
  }

    Hertz = sysconf(_SC_CLK_TCK);
    total = utime + stime + cutime + cstime;

    std::ifstream stream2(kProcDirectory + kUptimeFilename);
    if (stream2.is_open()) {
    std::getline(stream2, line);
    std::istringstream linestream(line); //allows us to read tokens
    linestream >> uptime_str >> token;
    uptime = std::stol(uptime_str);
    }
    
    seconds = uptime - ( starttime / Hertz );
    cpu_usage = 100 * (total / Hertz) / seconds;

    return cpu_usage; 

  }

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
string LinuxParser::Command(int pid) {
  
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }
  
  return line;
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {

  string line, key, value;
  int ram;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
            ram = (int) (stof(value) * (.001));
            break;
          }
      }
    }
  }
  return to_string(ram);
}

// TODO: Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  
  string line, key, value, uid;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
            uid = value;  
            break;
          }
      }
    }
  }
  
  return uid;
  }

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  
  string uid, line, usrname, x, value;
  
  // Get UID
  uid = Uid(pid);

  // Parse lines in etc/passwd
  std::ifstream filestream(kPasswordPath);
    if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while (linestream >> usrname >> x >> value) {
          if (value == uid) {
            break;
          }
        }
      }
    }
    return usrname;
  }

// DONE: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  
  string line, uptime, token;
  int counter = 1;
  long int uptime_int;

  string path = kProcDirectory + to_string(pid) + kStatusFilename;

  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line); //allows us to read tokens
    while(linestream >> token){
      if (counter ==  22){
          uptime_int = std::stol(token) / sysconf(_SC_CLK_TCK);
          break;
      }
      counter++;
    }
  }
  return uptime_int;
  }