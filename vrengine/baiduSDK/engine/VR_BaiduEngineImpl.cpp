#include "VR_BaiduEngineImpl.h"
#include "base/utils.h"
#include <fstream>

VR_BaiduEngineImpl::VR_BaiduEngineImpl()
    : m_speech(VR_BAIDU_ID, VR_BAIDU_AIPI_ID, VR_BAIDU_SECRET_KEY)
{

}

bool VR_BaiduEngineImpl::Initialize(spVR_MsgTaskBase task)
{
    LOGD_FUNC();
    m_spMsgTask = task;
}

void VR_BaiduEngineImpl::UnInitialize()
{

}

bool VR_BaiduEngineImpl::PostMessage(const std::string &message)
{
    TCLOGD("VR_BaiduEngineImpl::PostMessage [%s]", message.c_str());
    return m_spMsgTask->PostMessage(message);
}

void VR_BaiduEngineImpl::postRequest(const std::string& pcm)
{
    LOGD_FUNC();
    std::string file_content;
    aip::get_file_content(pcm.c_str(), &file_content);
    Json::Value result = m_speech.recognize(file_content, "pcm", 16000, aip::null);

    std::string strResult = result["result"][0].asString().c_str();

    if (strResult.compare("") == 0) {
        strResult = (boost::format(BaiduResultErrorMsg) %
                     result["err_no"].asString() %
                     result["err_msg"].asString()).str();
    }
    PostMessage(strResult);
}

bool VR_BaiduEngineImpl::buildTtsAudio(const std::string &path, const std::string& content, const buildTtsOptions& options)
{
    TCLOGD("VR_BaiduEngineImpl::buildTtsAudio path [%s]", path.c_str());

    std::ofstream ofile;
    std::string file_ret;

    std::map<std::string, std::string> _options;
    for (buildTtsIter it = options.begin(); it != options.end(); it++) {
        switch (it->first) {
        case VoiceRecog_Tts_Speed:
            _options["spd"] = it->second;
            break;
        case VoiceRecog_Tts_Pitch:
            _options["pit"] = it->second;
            break;
        case VoiceRecog_Tts_Volumn:
            _options["vol"] = it->second;
            break;
        case VoiceRecog_Tts_Person:
            _options["per"] = it->second;
            break;
        default:
            TCLOGD("build tts options is not find");
            break;
        }
    }

    ofile.open(path, std::ios::out | std::ios::binary);
    Json::Value result = m_speech.text2audio(content, _options, file_ret);

    if (!file_ret.empty()) {
        ofile << file_ret;
    }
    else {
        TCLOGD("build tts error %s", result.toStyledString().c_str());
    }
}

bool VR_BaiduEngineImpl::Start()
{

}

bool VR_BaiduEngineImpl::Stop()
{

}



