#include <iostream>

using namespace std;

template<typename T>
class MySharedPtr {
public:
    //构造函数
    MySharedPtr(T *ptr) : m_ptr(ptr) {
        m_userCount = new int(1);

        cout << "Constructor is called!" << endl;
    }

    //析构函数
    ~MySharedPtr() {
        //cout << "userCount: " << *m_userCount << endl;
        if (--(*m_userCount) == 0) {
            delete m_ptr;
            delete m_userCount; //userCount也是动态申请了，不要忘了
            m_ptr = nullptr;
            m_userCount = nullptr;

            cout << "Destructor is called!"  << endl;
        }
    }

    //拷贝构造
    MySharedPtr(const MySharedPtr<T> &rhs) {  //rhs --- right hand side
        m_ptr = rhs.m_ptr;
        m_userCount = rhs.m_userCount;
        ++(*m_userCount);

        cout << "Copy constructor is called!" << endl;
    }

    //拷贝赋值
    MySharedPtr &operator=(const MySharedPtr<T> &rhs) {
        //先提前增加引用计数，避免自我赋值提前释放内存
        ++(*rhs.m_userCount);

        if (--(*m_userCount) == 0) {
            delete m_ptr;
            delete m_userCount;
            m_ptr = nullptr;
            m_userCount = nullptr;

            cout << "Left side object is deleted!" << endl;
        }

        m_ptr = rhs.m_ptr;
        m_userCount = rhs.m_userCount;

        cout << "Assignment operator overloaded is called!" << endl;
        return *this;
    }

private:
    T *m_ptr;
    int *m_userCount;
};

int main()
{
    // Test Constructor and Assignment Operator Overloaded
    MySharedPtr<int> p1(new int(0));
    p1 = p1;
    // Test Copy Constructor
    MySharedPtr<int> p2(p1);
    // Test Assignment Operator Overloaded
    MySharedPtr<int> p3(new int(1));
    p3 = p1;

    return 0;
}