#include <pthread.h>
#include <iostream>
#include <functional>
#include <queue>
#include <thread>
#include <cassert>

using namespace std;

class ThreadPool {
public:
    static ThreadPool* getInstance() { //关键点：返回指针
        static ThreadPool instance;
        return &instance;
    }

    void init(int threadNum  = 8, int maxRequest = 10000){
        m_threadNum = threadNum;
        m_maxRequest = maxRequest;
        //在这里要init互斥锁，条件变量
        assert(threadNum > 0);
        for (int i = 0; i < m_threadNum; ++i) {
            thread(callback, getInstance()).detach();
        }
    }

    //工作线程（消费者）
    static void callback(ThreadPool *pool){ //★关键点：要传入ThreadPool指针，因为线程的回调函数是static的，不能用非static变量。
        while (true){ //关键点： 子线程是一直循环的
            pthread_mutex_lock(&pool->mutex);

            while (pool->tasks.empty() && !pool->shutdown){
                pthread_cond_wait(&pool->cond, &pool->mutex);
            }
            if (pool->shutdown){
                pthread_mutex_unlock(&pool->mutex);
                break;
            }

            auto task = move(pool->tasks.front());//关键点：用move变成右值
            pool->tasks.pop();
            pthread_mutex_unlock(&pool->mutex); //★★关键点：task()之前要释放互斥锁！！！

            task();
        }

    }

    //添加任务（生产者）
    template<typename F>
    void addTask(F&& task){  //关键点：返回void
        pthread_mutex_lock(&mutex); //★关键点：应在这里就加锁，因为if要访问task
        if ((int)tasks.size() < m_maxRequest){
            //☆关键点：使用forward做完美转发
            tasks.emplace(forward<F>(task));
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
    }


private:
    int m_threadNum;
    int m_maxRequest;
    bool shutdown;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
    queue<function<void()>> tasks;

    ThreadPool() {}
    ~ThreadPool(){
        pthread_mutex_lock(&mutex);
        shutdown = true;
        pthread_mutex_unlock(&mutex);
        pthread_cond_broadcast(&cond);

        //在这里destroy吗？（前边broadcast刚完，其他唤醒用完没？）
    }
};