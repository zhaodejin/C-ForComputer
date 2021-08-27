//
// Created by 赵德金 on 2021/8/22.
//

#ifndef C_FORCOMPUTER_ARRAY_H
#define C_FORCOMPUTER_ARRAY_H
#include <iostream>
using namespace std;
#define MAXSIZE  10
template <typename T>
class Array {
public:
    Array() = default;
    Array(int length);
    int size()const;
    void insertItem(const T &Item,int pos);
    void deleteItem(int pos);
    T& searchItem(int pos) const;
    void show();
    ~Array();

private:
    T *data;
    T length;
};
template <typename T>
Array<T>::Array(int size) {
    data = new T[MAXSIZE]{0};
    if(data == NULL)
    {
        cout<<"内存分配失败!"<<endl;
    }
    cout<<"请输入数据:\n";
    for (int i = 0; i< size; ++i) {
        cin>>data[i];
    }
    length = size;
}

template<typename T>
void Array<T>::insertItem(const T &Item, int pos) {
    if(length == MAXSIZE)
    {
        cout<<"超过线性表的最大长度！指定位置插入元素失败！\n";
        return;
    }
    if(pos<1||pos>length+1)
    {
        cout<<"位置越界！无法在指定位置插入元素\n";
        return;
    }
    for (int j = length-1; j >= pos-1; j--) {
        data[j+1] = data[j];
    }
    data[pos-1] = Item;
    length++;
    return;
}

template<typename T>
void Array<T>::deleteItem(int pos) {
    if(pos<1||pos>length+1)
    {
        cout<<"位置越界！无法在指定位置插入元素\n";
        return;
    }
    for (int k = pos; k < length; ++k) {
        data[k-1] = data[pos];
    }
    length--;
    return;
}

template<typename T>
int Array<T>::size() const{
    return length;
}

template<typename T>
T &Array<T>::searchItem(int pos) const{
    if (pos < 1 || pos > length)
    {
        cout << "位置越界！返回第一个元素！" << endl;
        return data[0];
    }
    return data[pos-1];
}

template<typename T>
Array<T>::~Array() {

}

template<typename T>
void Array<T>::show() {
    if(length == 0)
    {
        cout<<"没有元素\n"<<endl;
        return;
    }
    for (int i = 0; i <length; ++i) {
        cout<<data[i]<<'\t';
    }
    cout<<endl;
}



#endif //C_FORCOMPUTER_ARRAY_H
