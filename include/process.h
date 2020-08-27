#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

#include "linux_parser.h"

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  //Process(int pid){ pid_ = pid; cpuUtil_ = CpuUtilization();} // Constructor, sets PID for each process
  Process(int pid){ pid_ = pid; setCPU(); setRAM(); } // Constructor: sets PID, calculates CPU and RAM for each process
 
  void setCPU();
  void setRAM();
  int Pid();                               // DONE: See src/process.cpp
  std::string User();                      // DONE: See src/process.cpp
  std::string Command();                   // DONE: See src/process.cpp
  float CpuUtilization();                  // DONE: See src/process.cpp
  std::string Ram();                       // DONE: See src/process.cpp
  long int UpTime();                       // DONE: See src/process.cpp
  bool operator<(Process const& a) const;  // DONE: See src/process.cpp

  // DONE: Declare any necessary private members
 private:
    int pid_;
    float cpuUtil_;
    std::string ram_;

};

#endif