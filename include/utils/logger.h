#ifndef __logger__
#define __logger__
#include <iostream>
#include <iomanip>
#include <stdint.h> 
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
using std::string;
using std::endl;
using std::to_string;
using std::ios;
string currTime();


class Logger {
public:
    enum log_level {DEBUG,INFO,WARNING,ERROR,FATAL};
    enum log_target{file,terminal,file_and_terminal};
    string path;
    std::ofstream outfile;

private: 
  
    log_target target;
    
    log_level level;
    void output(string text,log_level act_level);
   
    Logger(log_target target, log_level level, string path);
    Logger(); 
    static Logger* instance;

public:
    static Logger* getInstance();
 
    Logger(const Logger &);
    void debug(string text);
    void info(string text);
    void warning(string text);
    void error(string text);
    void fatal(string text);
};

#endif