#ifndef VR_ENGINE
#define VR_ENGINE

#include "VR_EngineBase.h"
#include "VR_MsgTaskBase.h"
#include <boost/shared_ptr.hpp>
#include "VR_BaiduEngine.h"
#include "config.h"


class VR_Engine : public VR_EngineBase
{
public:
    VR_Engine();
    virtual ~VR_Engine();
    virtual void ProcessMessage(const std::string& message);
    void Initialize(spVR_MsgTaskBase base);
    void setBaiduEngine(bool flag);
    void postRequest(const std::string& msg);
private:
    spVR_BaiduEngine m_spBaiduEngine;
    bool m_BaiduEngineFlag;
};

#endif // VR_ENGINE

