#ifndef SYNC
#define SYNC
#include <pthread.h>

class MySync
{
public:
    MySync();
    virtual ~MySync();

    void SyncStart();
    bool TrySyncStart();
    void SyncEnd();

private:
    MySync(const MySync& src) {}
    MySync& operator = (const MySync& src) { return *this; }

    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;
};

class Sync
{
public:
    Sync(MySync& cSync);
    ~Sync();

private:
    Sync(const Sync& cSync);
    Sync& operator=(const Sync& cSync);

    MySync* m_sync;
};


#endif // SYNC

