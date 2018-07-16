#ifndef VR_ENGINEIF
#define VR_ENGINEIF
#include "VR_MsgTaskBase.h"
#include <string>
#include <config.h>

class VR_EngineIF
{
public:
    virtual ~VR_EngineIF() {}

    virtual bool Initialize(spVR_MsgTaskBase task) = 0;
    virtual bool Start() = 0;
    virtual bool Stop() = 0;
    virtual void UnInitialize() = 0;

    virtual bool PostMessage(const std::string& message) = 0;
    virtual void postRequest(const std::string& pcm) = 0;
//    virtual void startRecordMicData() = 0;
//    virtual void stopRecordMicData() = 0;
//    virtual int onAudioInData(int16_t* buffer, int32_t size) = 0;
};

#endif // VR_ENGINEIF

