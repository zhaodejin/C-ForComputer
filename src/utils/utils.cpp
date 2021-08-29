//
// Created by 赵德金 on 2021/8/21.
//
#include "utils/utils.h"
#include <algorithm>
#include <cctype>
#include <cstring>
#include "DataStruct/Array.h"
#include "DataStruct/RBTree.h"
#include "Networks/boostHttp.h"
#include "Networks/boostUDPServer.h"
//#include "Networks/boostUDPClient.h"
#include <thread>
#include "DataStruct/Graph.h"
#include "DataStruct/LinkList.h"
//logger = new Logger(Logger::file_and_terminal, Logger::DEBUG, "result.log");
using namespace std;
using namespace boost::asio;

Logger logger(Logger::file_and_terminal, Logger::DEBUG,"result.log");
Logger &initLogger() {
    Logger *logger = Logger::getInstance();
    return *logger;
}

void UDPClient()
{
    
    try{
        cout<<"UDP客户端开启:"<<endl;
        io_service ios;
        ip::udp::endpoint send_ep(ip::address::from_string("192.168.0.105"),6699);
        ip::udp::socket sock(ios);
        sock.open(ip::udp::v4());
        char buf[1];
        sock.send_to(buffer(buf),send_ep);
        vector<char> v(100,0);
        ip::udp::endpoint recv_ep;
        sock.receive_from(buffer(v),recv_ep);
        cout<<"接收到了来自："<<recv_ep.address()<<"的数据"<<endl;
        cout<<&v[0]<<endl;
    }
    catch (std::exception &e)
    {
        cerr<<e.what()<<endl;
    }
}
const string toUpper(string &str){
    for (int i = 0; i < str.size(); ++i) {
        if ((str[i]>='a')&&(str[i]<='z'))
        {
            str[i]-=32;
        }
    }
    return str;
}
void udp(){
    UDPClient();
    std::thread udpclient(serveUDP);
    udpclient.join();
    //udpclient.detach();
}
void remainder(string className) {
    
    cout<<"######################################################################\n";
    cout<<"######################################################################\n";
    cout<<"###                                                                ###\n";
    cout<<"###                                                                ###\n";
    cout<<"                     欢迎来到 "<<toUpper(className)<<" 世界!                             \n";
    cout<<"                     根据提示进行你的操作:                        \n";
    cout<<"###                                                                ###\n";
    cout<<"###                                                                ###\n";
    cout<<"######################################################################\n";
    cout<<"######################################################################\n";
    //logger.debug("####################################################");
}

void mainMenu() {
    cout<<"<============================请输入你的操作===========================>\n";
    cout<<"###      1.数据结构"<<endl;
    cout<<"###      2.计算机网络\n";
    cout<<"###      3.操作系统\n";
    cout<<"###      4.计算机组成原理\n";
    cout<<"<============================请输入你的操作===========================>\n";
    
    int mainOptNum;
    cin>>mainOptNum;
    //Logger *logger = new Logger(Logger::file_and_terminal, Logger::DEBUG, "result.log");
    switch (mainOptNum)
    {
        

        case DATASTRUCT:
            remainder("数据结构");
            dataStructMenu();
            //logger->debug("数据结构已经运行");
            break;
        case NETWORK:
            remainder("计算机网络");
            httpTest();
            //logger->info("计算机网络已经运行");
            break;
        case OPERATIONSYSTEM:
            remainder("操作系统");
            operatorOS();
            break;
        case BUILDPRINCIPLE:
            remainder("计算机组成原理");
            break;
        default:
            break;

    }

}

void dataStructMenu() {
    cout<<"<============================请输入你的操作===========================>\n";
    cout<<"###      1.数组"<<endl;
    cout<<"###      2.链表\n";
    cout<<"###      3.队列\n";
    cout<<"###      4.栈\n";
    cout<<"###      5.二叉树"<<endl;
    cout<<"###      6.红黑树\n";
    cout<<"###      7.二叉搜索树\n";
    cout<<"###      8.图\n";
    cout<<"<============================请输入你的操作===========================>\n";
    int dataStructOptNum;
    cin>>dataStructOptNum;
    switch (dataStructOptNum)
    {
        case ARRAY:
            remainder("数组");
            operatorArray();
            break;
        case LIST:
            remainder("链表");
            operatorLinkList();
            break;
        case QUEUE:
            remainder("队列");
            break;
        case STACK:
            remainder("栈");
            break;
        case BINARYTREE:
            remainder("二叉树");
            break;
        case BRTREE:
            remainder("红黑树");

            break;
        case BSTREE:
            remainder("二叉搜索树");
            break;
        case GRAPH:
            remainder("图");
            callGraph();
            break;
        default:
            break;

    }

}

void operatorLinkList() {
    cout<<"<============================请输入你的操作===========================>\n";
    cout<<"###      1.创建链表： "<<endl;
    cout<<"###      2.插入链表\n";
    cout<<"###      3.删除链表\n";
    cout<<"###      4.查找\n";
    cout<<"###      5.长度"<<endl;
    cout<<"<============================请输入你的操作===========================>\n";


        int listOptNum;
        cin>>listOptNum;
        DLinklist<int> linkList;
        switch (listOptNum) {
        case CEATELINKLIST:
            linkList.length();
            break;
        case INSRETLINKLIST:
            cout << "输入你要插入的元素：";
            int number;
            cin >> number;
            linkList.insertNode(number);
            break;
        case DELETELINKLIST:
            cout << "请输入要删除的数：" << endl;
            int item;     
            cin >> item,
            linkList.deleteNode(item);
            break;
        case SEARCHLINKLIST:
            cout << "请输入查找元素： ";
            int findNode;
            cin >> findNode;
            linkList.searchNode(findNode);
            break;
        case RETURNLENGTH:
            cout << "数组长度为：" << linkList.length() << endl;
            break;
        default:
            operatorLinkList();
            break;
            }

      /*  cout << L.searchItem(2) << endl;
    L.deleteItem(1);
    L.show();
    L.insertItem('c', 3);
    L.show();*/
}
void operatorOS()
{
    cout << "<============================请输入你的操作===========================>\n";
    cout << "###      1.线程池： " << endl;
    cout << "###      2.内存管理\n";
    cout << "###      3.文件管理\n";
    cout << "###      4.进程表\n";
    cout << "###      5.IO" << endl;
    cout << "<============================请输入你的操作===========================>\n";

    int OSoptNum;
    cin >> OSoptNum;
    switch (OSoptNum)
    {
    case THREAD:
        //execute_with_threadpool();
        break;
    case MEMORYMANAGER:
        schedule();
        break;
    case FILEMANAGER:
        break;
    case PROCESSTABLE:
        break;
    case IO:
        break;
    default:
        operatorOS();
        break;
    }
}

void operatorArray()
{
    Array<int> L(MAXSIZE);
    cout << "<============================请输入你的操作===========================>\n";
    cout << "###      1.显示当前数组： " << endl;
    cout << "###      2.删除\n";
    cout << "###      3.插入\n";
    cout << "###      4.按位置查找\n";
    cout << "###      5.长度" << endl;
    cout << "<============================请输入你的操作===========================>\n";

    int arrayOptNum;
    cin >> arrayOptNum;
    switch (arrayOptNum)
    {
    case ARRAYSHOW:
        L.show();
        break;
    case ARRAYDELETE:
        cout << "输入你要删除元素的位置：";
        int pos;
        cin >> pos;
        L.deleteItem(pos);
        cout << "当前数组为：";
        L.show();
        break;
    case ARRAYINSERT:
        cout << "请输入插入的项和位置" << endl;
        int item;
        int insertPos;
        cin >> item,
            cin >> insertPos;
        L.insertItem(item, insertPos);
        cout << "当前数组为：";
        L.show();
        break;
    case ARRAYFIND:
        cout << "请输入查找元素的位置： ";
        int findPos;
        cin >> findPos;
        L.searchItem(findPos);
        cout << "当前数组为：";
        L.show();
        break;
    case ARRAYSIZE:
        cout << "数组长度为：" << L.size() << endl;
        break;
    default:
        operatorArray();
        break;
    }

    /*  cout << L.searchItem(2) << endl;
    L.deleteItem(1);
    L.show();
    L.insertItem('c', 3);
    L.show();*/
}