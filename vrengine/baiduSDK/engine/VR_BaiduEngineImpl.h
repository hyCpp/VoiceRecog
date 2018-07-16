#ifndef VR_BAIDUENGINEIMPL
#define VR_BAIDUENGINEIMPL

#include "VR_EngineIF.h"
#include "config.h"
#include "speech.h"

class VR_BaiduEngineImpl : public VR_EngineIF
{
public:
    VR_BaiduEngineImpl();
    bool Initialize(spVR_MsgTaskBase task);
    virtual bool Start();
    virtual bool Stop();
    virtual void UnInitialize();

    virtual bool PostMessage(const std::string& message);
    virtual void postRequest(const std::string& pcm);
    virtual bool buildTtsAudio(const std::string &path, const std::string& content, const buildTtsOptions& options);

private:
    spVR_MsgTaskBase m_spMsgTask;
    aip::Speech m_speech;
};

#endif // VR_BAIDUENGINEIMPL

