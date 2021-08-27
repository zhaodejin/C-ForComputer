#include "utils/utils.h"
#include <boost/bind.hpp>
#include <boost/threadpool.hpp>
using namespace boost::threadpool;
void first_task();
void second_task();
void third_task();
void task_with_parameters(int vaule, string str);
void execute_with_threadpool();
void first_task()
{
    for (int i = 0; i < 30; i++)
        cout << "first" << i << endl;
}

void second_task()
{
    for (int i = 0; i < 30; i++)
        cout << "second" << i << endl;
}

void third_task()
{
    for (int i = 0; i < 30; i++)
        cout << "third" << i << endl;
}
void task_with_parameters(int value, string str)
{
    cout << "task_with_parameters with int =" << value << endl;
    cout << "task_with_parameters with string =" << str << endl;
}

void execute_with_threadpool()
{
    pool pooltest(2);
    pooltest.schedule(&first_task);
    pooltest.wait(); //<span style="white-space:pre"> </span>
    pooltest.schedule(&second_task);
    pooltest.wait();
    pooltest.schedule(&third_task);
    pooltest.schedule(boost::bind(task_with_parameters, 8, "This is a message of thread!"));
    pooltest.schedule(&third_task);
    while (1)
    {
        ;
    }
}