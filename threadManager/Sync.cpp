#include "Sync.h"

MySync::MySync()
{
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);
}

MySync::~MySync()
{
    pthread_mutexattr_destroy(&attr);
    pthread_mutex_destroy(&mutex);
}

bool MySync::TrySyncStart()
{
    int ret = pthread_mutex_trylock(&mutex);
    return (ret == 0) ? true : false;
}

void MySync::SyncStart()
{
    pthread_mutex_lock(&mutex);
}

void MySync::SyncEnd()
{
    pthread_mutex_unlock(&mutex);
}


Sync::Sync(MySync &cSync)
    : m_sync(&cSync)
{
    if (m_sync) m_sync->SyncStart();
}

Sync::~Sync()
{
    if (m_sync) m_sync->SyncEnd();
}
