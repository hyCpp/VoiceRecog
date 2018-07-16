#ifndef VR_MSGTASK
#define VR_MSGTASK

#include "VR_MsgTaskBase.h"
#include "Runnable.h"
#include "Sync.h"
#include <queue>
#include <VR_EngineIF.h>
#include <VR_Engine.h>

class VR_MsgTask : public VR_MsgTaskBase, public Runnable, public boost::enable_shared_from_this<VR_MsgTask>
{
public:
    VR_MsgTask();
    VR_MsgTask(const std::string& pName);
    void Initialize(spVR_Engine engine);
    virtual ~VR_MsgTask();
    bool run();
    virtual bool PostMessage(const std::string& message);
    void StartVRThread();

private:
    MySync m_sync;
    std::queue<std::string> m_MsgQueue;
    spVR_Engine m_spEngine;
};

#endif // VR_MSGTASK

