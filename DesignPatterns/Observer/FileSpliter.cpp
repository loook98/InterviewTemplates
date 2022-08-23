#include <vector>
#include <list>
#include <iostream>

using namespace std;

//抽象类观察者
class IProgress{
public:
    virtual void doProgress()=0;
};

//具体的观察者
//1.控制台形式的观察者
class ConsoleNotifier:public IProgress{
public:
    void doProgress() override {
        cout << "...";
    }
};

//2. ....

//使用
//内部放一个IProgress类型链表即可，每个IProgress的通知代码编写是一样的，会在运行时执行不同Progress的处理函数
class FileSpliter{
public:
    void addProgress(IProgress *ip){}
    void rmProgress(IProgress *ip){}
    //通知所有观察者
    void Notify(){
        for (auto progress: iProgressList) {
            progress->doProgress();
        }
    }
private:
    list<IProgress*> iProgressList;
};
