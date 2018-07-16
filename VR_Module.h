#ifndef VR_MODULE
#define VR_MODULE
#include "VR_Engine.h"
#include "VR_MsgTask.h"

class VR_Module
{
public:
    ~VR_Module();
    static VR_Module* getInstance();
    void Initialize();
    void Start();

    VR_Engine* getEnginePtr();

private:
    VR_Module();
    VR_Module(const VR_Module&);
    VR_Module& operator = (const VR_Module&);

    static spVR_Module m_spModule;
    spVR_Engine m_spEngine;
    spVR_MsgTask m_spMsgTask;
};

#endif // VR_MODULE

