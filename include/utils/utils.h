//
// Created by 赵德金 on 2021/8/21.
//

#ifndef C_FORCOMPUTER_UTILS_H
#define C_FORCOMPUTER_UTILS_H
#include <string>
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<ostream>
#include<boost/static_string.hpp>
#include <boost/asio.hpp>
#include <algorithm>
#include <vector>
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<stdio.h>
#include<ostream>
#include<boost/static_string.hpp>
#include <boost/asio.hpp>
#include<boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <boost/system/error_code.hpp>
#include "utils/logger.h"
#include "utils/config.h"
#include "os/pageSchedule.h" 

//extern Logger *logger;
//extern Logger *logger;
Logger &initLogger();

using namespace std;
enum dataStruct{
    ARRAY = 1,
    LIST,
    QUEUE,
    STACK,
    BINARYTREE,
    BRTREE,
    BSTREE,
    GRAPH,
};
enum Network{
    DNS = 0,
    PROTOCOL,
    TCPIP,
    UDP,
    IPTABELS,
    HTTP,
};

enum operationSystem{
    THREAD = 1,
    MEMORYMANAGER,
    FILEMANAGER,
    PROCESSTABLE,
    IO,
};
enum buildPrinciple{
    VIRTURALMEMORY = 0,
    PAGETABLES,
};

enum computer{
    DATASTRUCT = 1,
    NETWORK,
    OPERATIONSYSTEM,
    BUILDPRINCIPLE,
};

enum ArrayList{
    ARRAYSHOW = 1,
    ARRAYDELETE,
    ARRAYINSERT,
    ARRAYFIND,
    ARRAYSIZE,
};

enum LinkedList{
    CEATELINKLIST = 1,   
    INSRETLINKLIST,
    DELETELINKLIST,
    SEARCHLINKLIST,
    RETURNLENGTH,
};

void remainder(string className);
void mainMenu();
void dataStructMenu();
void operatorArray();
void operatorLinkList();
void operatorOS();
void udp();


#endif //C_FORCOMPUTER_UTILS_H