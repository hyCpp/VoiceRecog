#ifndef VR_ENGINEBASE
#define VR_ENGINEBASE

#include <string>

class VR_EngineBase
{
public:
    virtual ~VR_EngineBase() {}

    virtual void ProcessMessage(const std::string& message) = 0;
};

#endif // VR_ENGINEBASE

