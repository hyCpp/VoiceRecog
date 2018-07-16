#ifndef THREAD
#define THREAD
#include"Runnable.h"
#include <stdio.h>

class Runnable;
struct ThreadData
{
    Runnable* thread;
};

class Thread
{
public:
    Thread();
    ~Thread();

    virtual bool createThread(Runnable *mThread, unsigned long stack_size = 8 * 1024);
    virtual void sleepSec(unsigned long sec);
    static void entryThread(ThreadData *threadParm);

    virtual void notify();
    virtual void wait();
private:
    pthread_t m_ThreadId;
    pthread_attr_t m_Thread_Attr;
    pthread_cond_t m_cond;
    pthread_mutex_t m_mutex;
    pthread_mutexattr_t m_attr;
};


#endif // THREAD

