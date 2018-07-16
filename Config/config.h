#ifndef CONFIG
#define CONFIG
#include "Log_Func.h"
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/format.hpp>
#include <map>

#define VR_DECLARE_CLASS_WITH_SMART_PTR(CLASS_NAME)         \
    class CLASS_NAME;                                       \
    typedef boost::shared_ptr<CLASS_NAME> sp##CLASS_NAME;   \
    typedef boost::weak_ptr<CLASS_NAME> wp##CLASS_NAME;

VR_DECLARE_CLASS_WITH_SMART_PTR(VR_MsgTaskBase)
VR_DECLARE_CLASS_WITH_SMART_PTR(VR_MsgTask)
VR_DECLARE_CLASS_WITH_SMART_PTR(VR_Module)
VR_DECLARE_CLASS_WITH_SMART_PTR(VR_EngineIF)
VR_DECLARE_CLASS_WITH_SMART_PTR(VR_EngineBase)
VR_DECLARE_CLASS_WITH_SMART_PTR(VR_BaiduEngine)
VR_DECLARE_CLASS_WITH_SMART_PTR(VR_Engine)
VR_DECLARE_CLASS_WITH_SMART_PTR(Runnable)
VR_DECLARE_CLASS_WITH_SMART_PTR(VR_BaiduEngineImpl)

static const std::string VR_BAIDU_ID("10970975");
static const std::string VR_BAIDU_AIPI_ID("RhcYvu6ddMRbwqRRSwUkDVQS");
static const std::string VR_BAIDU_SECRET_KEY("QlkLy2jkUlcREoUp2Yb6Vlu5fiyyPO9h");

const std::string BaiduResultErrorMsg("<event errcode = \"%1%\" msgtext = \"%2%\"></event>");

enum buildTtsType
{
    VoiceRecog_Tts_Speed,
    VoiceRecog_Tts_Pitch,
    VoiceRecog_Tts_Volumn,
    VoiceRecog_Tts_Person,
};

typedef std::map<buildTtsType, std::string> buildTtsOptions;
typedef std::map<buildTtsType, std::string>::const_iterator buildTtsIter;

#endif // CONFIG

