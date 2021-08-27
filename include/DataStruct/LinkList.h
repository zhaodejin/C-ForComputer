#ifndef SMART_DLINKLIST_H_
#define SMART_DLINKLIST_H_

#include <boost/smart_ptr.hpp>
#include <iostream>

using namespace std;
template <typename T>
struct LNode
{
public:
    boost::shared_ptr<T> data;
    boost::weak_ptr<LNode<T>> prior;
    boost::shared_ptr<LNode<T>> next;
};

template <typename T>
class DLinklist
{
private:
    int len;
    boost::shared_ptr<LNode<T>> head;

public:
    DLinklist();
    ~DLinklist();
    int length() const { return len; }
    bool isEmpty() const { return (0 == len) ? true : false; }
    boost::shared_ptr<LNode<T>> searchNode(T data) const;
    void insertNode(T data);
    bool deleteNode(T nodeData);
};
template <typename T>
DLinklist<T>::DLinklist() : len(0)
{
    boost::shared_ptr<LNode<T>> head(nullptr);
}
template <typename T>
DLinklist<T>::~DLinklist()
{
    head.reset();
}
template <typename T>
boost::shared_ptr<LNode<T>> DLinklist<T>::searchNode(T data) const
{
    boost::shared_ptr<LNode<T>> dstNode(new LNode<T>);
    if (isEmpty())
    {
        cout << "the searched list is empty.\n";
        return nullptr;
    }
    else
    {
        dstNode = head;
        while (dstNode.get() && *(dstNode->data) != data)
        {
            dstNode = dstNode->next;
        }
        if (dstNode.get())
        {
            cout << "the data " << *(dstNode->data) << " has been found in the list.\n";
            return dstNode;
        }
        else
        {
            cout << "we have searched all the list, the data " << data << " is not found\n";
            return nullptr;
        }
    }
}

template <typename T>
void DLinklist<T>::insertNode(T data)
{
    boost::shared_ptr<T> temp(new T(data));
    boost::shared_ptr<LNode<T>> newNode(new LNode<T>);
    newNode->data = temp;
    if (head.get())
    {
        newNode->next = head;
        head->prior = newNode;
    }
    else
        newNode->next = nullptr;
    newNode->prior.reset();
    head = newNode;
    len++;
    cout << "one node is inserted,and the node is: " << data << " \n";
}
template <typename T>
bool DLinklist<T>::deleteNode(const T nodeData)
{
    boost::shared_ptr<LNode<T>> dstNode;
    if (isEmpty())
    {
        std::cout << "the list is empty." << std::endl;
        return false;
    }
    else if (dstNode ==  searchNode(nodeData))
    {
        boost::shared_ptr<LNode<T>> temp(new LNode<T>);
        temp = dstNode->prior.lock();
        //if the node is the first node that head point to
        if (!temp.get())
        {
            this->head = dstNode->next;
            dstNode->prior.reset();
        }
        else if (dstNode->next.get())
        {
            //the node is not the first,judge the node whether it is the last or not
            temp->next = dstNode->next;
            //dstNode->prior.lock()->next = dstNode->next;
            dstNode->next->prior = dstNode->prior;
        }
        else
        {
            temp->next = nullptr;
        }
        --len;
        std::cout << "one node has been deleted,the number of list is: " << len << " \n";
        return true;
    }
    else
    {
        std::cout << "the nodeData is not found.\n";
        return false;
    }
}

#endif
