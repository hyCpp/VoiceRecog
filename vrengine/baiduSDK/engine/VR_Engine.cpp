#include "VR_Engine.h"

VR_Engine::VR_Engine()
    : m_BaiduEngineFlag(false)
{
    LOGD_FUNC();
}

VR_Engine::~VR_Engine()
{

}

void VR_Engine::Initialize(spVR_MsgTaskBase base)
{
    LOGD_FUNC();
    m_spBaiduEngine = boost::make_shared<VR_BaiduEngine>();
    m_spBaiduEngine->Initialize(base);
}


void VR_Engine::ProcessMessage(const std::string &message)
{
    LOGD_FUNC();
    if (m_BaiduEngineFlag) {
        m_spBaiduEngine->ProcessMessage(message);
    }
}

void VR_Engine::setBaiduEngine(bool flag)
{
    m_BaiduEngineFlag = flag;
}

void VR_Engine::postRequest(const std::string& msg)
{
    m_spBaiduEngine->postRequest(msg);
}
