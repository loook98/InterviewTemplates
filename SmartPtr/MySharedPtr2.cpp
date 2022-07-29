#include <bits/stdc++.h>

using namespace std;

//第二次自己写智能指针
template<typename T>
class MySharedPtr{
private:
    T *m_ptr; //原始指针
    int *m_count; //指向*m_ptr的指针个数

public:
    explicit MySharedPtr(T *p) : m_ptr(p){
        m_count = new int(1);

        cout << "Ctor called" << endl;
    }

    ~MySharedPtr(){
        if(--(*m_count) == 0){
            delete m_ptr;
            delete m_count;

            m_ptr = nullptr;
            m_count = nullptr;

            cout << "Dtor called" << endl;
        }
    }
    MySharedPtr(const MySharedPtr<T> &other){
        ++(*other.m_count);

        m_ptr = other.m_ptr;
        m_count = other.m_count;

        cout << "Copy constructor is called!" << endl;
    }

    MySharedPtr<T>& operator=(const MySharedPtr<T> &other){
        //IDE提醒没有处理自我赋值才加上了这个
        if (this == &other)
            return *this;

        //防止自我赋值
        ++(*other.m_count); //其实这都达不到防止自我赋值的目的了，刚开始那两行如果是自我赋值都直接跳出了。

        if(--(*m_count) == 0){
            delete m_ptr;
            delete m_count;

            cout << "Left side object is deleted!" << endl;
        }

        m_ptr = other.m_ptr;
        m_count = other.m_count;

        cout << "Assignment operator overloaded is called!" << endl;
        return *this;
    }
};

int main(){
    MySharedPtr<int> p1(new int(456));

    MySharedPtr<int> p2(new int(123));

    p2 = p1;
}