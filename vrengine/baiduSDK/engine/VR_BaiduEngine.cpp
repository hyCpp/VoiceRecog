#include "VR_BaiduEngine.h"

VR_BaiduEngine::VR_BaiduEngine()
{
    LOGD_FUNC();
}

void VR_BaiduEngine::Initialize(spVR_MsgTaskBase base)
{
    LOGD_FUNC();
    m_spBaiduEngineImpl = boost::make_shared<VR_BaiduEngineImpl>();
    m_spBaiduEngineImpl->Initialize(base);
}


void VR_BaiduEngine::ProcessMessage(const std::string &message)
{
    LOGD_FUNC();
    LOGD("message = %s", message.c_str());
}


void VR_BaiduEngine::postRequest(const std::string& msg)
{
    m_spBaiduEngineImpl->postRequest(msg);
}
