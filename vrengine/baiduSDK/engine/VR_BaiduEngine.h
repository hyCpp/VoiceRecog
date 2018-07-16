#ifndef VR_BAIDUENGINE
#define VR_BAIDUENGINE
#include "VR_EngineBase.h"
#include "VR_MsgTaskBase.h"
#include <boost/shared_ptr.hpp>
#include "config.h"
#include "VR_BaiduEngineImpl.h"


class VR_BaiduEngine : public VR_EngineBase
{
public:
    VR_BaiduEngine();
    virtual void ProcessMessage(const std::string& message);
    void Initialize(spVR_MsgTaskBase base);

    void postRequest(const std::string& msg);

private:
    spVR_BaiduEngineImpl m_spBaiduEngineImpl;
};

#endif // VR_BAIDUENGINE

