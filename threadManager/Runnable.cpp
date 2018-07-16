#include "Runnable.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <unistd.h>
#include "config.h"

Runnable::Runnable()
{
    LOGD_FUNC();
}

Runnable::Runnable(const std::string& pName)
{
    m_Thread_Name = pName;
    m_spThread = boost::make_shared<Thread>();
}

Runnable::~Runnable()
{
}

void Runnable::ThreadEntry()
{
    run();
}

bool Runnable::StartThread()
{
    if (!m_spThread->createThread(this)) {
        TCLOGD("Create Thread Fail...");
        return false;
    }
}

void Runnable::Notify()
{
    m_spThread->notify();
}

void Runnable::Wait()
{
    m_spThread->wait();
}
