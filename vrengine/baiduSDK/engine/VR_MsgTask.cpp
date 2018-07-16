#include "VR_MsgTask.h"

VR_MsgTask::VR_MsgTask()
{
    LOGD_FUNC();
}

VR_MsgTask::VR_MsgTask(const std::string &pName)
    : Runnable(pName)
{
    LOGD_FUNC();
}

VR_MsgTask::~VR_MsgTask()
{

}

void VR_MsgTask::Initialize(spVR_Engine engine)
{
    m_spEngine = engine;
}

bool VR_MsgTask::run()
{
    while (true) {
        if (m_MsgQueue.empty()) {
            Wait();
        }

        while (!m_MsgQueue.empty()) {
            std::string msg("");
            {
                Sync _sync(m_sync);
                msg = m_MsgQueue.front();
                m_MsgQueue.pop();
            }

            if (!msg.empty()) {
                m_spEngine->ProcessMessage(msg);
            }
        }
    }
}

bool VR_MsgTask::PostMessage(const std::string &message)
{
    {
        Sync _sync(m_sync);
        m_MsgQueue.push(message);
    }
    Notify();
}

void VR_MsgTask::StartVRThread()
{
    LOGD_FUNC();
    this->StartThread();
}
