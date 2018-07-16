#ifndef VR_MSGTASKBASE
#define VR_MSGTASKBASE
#include <string>

class VR_MsgTaskBase
{
public:
    VR_MsgTaskBase() {}
    virtual ~VR_MsgTaskBase() {}

    virtual bool PostMessage(const std::string& message) = 0;
};

#endif // VR_MSGTASKBASE

