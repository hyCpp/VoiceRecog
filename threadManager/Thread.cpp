#include "Thread.h"
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <Log_Func.h>

Thread::Thread()
    : m_cond(PTHREAD_COND_INITIALIZER)

{
    pthread_mutexattr_init(&m_attr);
    pthread_mutexattr_settype(&m_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&m_mutex, &m_attr);
}

Thread::~Thread()
{
    pthread_mutexattr_destroy(&m_attr);
    pthread_mutex_destroy(&m_mutex);
}

void Thread::entryThread(ThreadData *threadParm)
{
    if (threadParm->thread != NULL) {
        threadParm->thread->ThreadEntry();
    }
    else {
        TCLOGD("Thread Error...");
    }
    delete threadParm;
    threadParm = NULL;
    pthread_exit(0);
}

bool Thread::createThread(Runnable *mThread, unsigned long stack_size)
{
    int err;
    if (mThread == NULL) {
        TCLOGD("CreateThread() : Thread pointer is NULL!  Can't begin the thread... ");
        return false;
    }

    pthread_attr_init(&m_Thread_Attr);
    pthread_attr_setschedpolicy(&m_Thread_Attr, SCHED_FIFO);
    pthread_attr_setscope(&m_Thread_Attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setstacksize(&m_Thread_Attr, stack_size);

    ThreadData* threadData = new ThreadData;
    threadData->thread = mThread;

    err = pthread_create(&m_ThreadId, &m_Thread_Attr, (void* (*)(void*))entryThread, threadData);

    if (err != 0) {
        TCLOGD("CreateThread() : Failed to create and start the thread!");
        m_ThreadId = 0;
        return false;
    }

    pthread_detach(m_ThreadId);

    return true;
}

void Thread::notify()
{
    pthread_mutex_lock(&m_mutex);
    pthread_cond_signal(&m_cond);
    pthread_mutex_unlock(&m_mutex);
}

void Thread::wait()
{
    pthread_mutex_lock(&m_mutex);
    pthread_cond_wait(&m_cond, &m_mutex);
    pthread_mutex_unlock(&m_mutex);
}

void Thread::sleepSec(unsigned long sec)
{
    sleep(sec);
}
