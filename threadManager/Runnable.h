#ifndef RUNNABLE
#define RUNNABLE
#include <string>
#include "Thread.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
class Thread;

class Runnable
{
public:
    Runnable();
    Runnable(const std::string& pName);
    virtual ~Runnable();

    void ThreadEntry();

    virtual bool run() = 0;
    virtual bool StartThread();
    virtual void Notify();
    virtual void Wait();
public:
    boost::shared_ptr<Thread> m_spThread;
    std::string m_Thread_Name;
};
#endif // RUNNABLE

