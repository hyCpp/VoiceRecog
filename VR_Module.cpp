#include "VR_Module.h"
#include <boost/make_shared.hpp>

spVR_Module VR_Module::m_spModule = nullptr;

VR_Module::VR_Module()
{

}

VR_Module::~VR_Module()
{

}

VR_Module* VR_Module::getInstance()
{
    LOGD_FUNC();

    if (m_spModule.get() == nullptr) {
        m_spModule = boost::shared_ptr<VR_Module>(new VR_Module);
    }

    return m_spModule.get();
}


void VR_Module::Initialize()
{
    LOGD_FUNC();
    m_spMsgTask = boost::make_shared<VR_MsgTask>("VR_MainTask");
    m_spEngine = boost::make_shared<VR_Engine>();

    m_spEngine->Initialize(m_spMsgTask);
    m_spMsgTask->Initialize(m_spEngine);
}

void VR_Module::Start()
{
    LOGD_FUNC();
    m_spMsgTask->StartVRThread();
}

VR_Engine* VR_Module::getEnginePtr()
{
    if (m_spEngine.get() != nullptr) {
        return m_spEngine.get();
    }
    return nullptr;
}
