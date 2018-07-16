
#include "Log_Func.h"
#include "Log_Func.cpp"
//#include "VR_Module.h"
//#include "CurlHttp.h"
#include "VR_CurlHttpTool.h"
using namespace std;

//void testPostAudio(VR_Module* vr)
//{
//    LOGD_FUNC();
//    sleep(2);
//    vr->getEnginePtr()->setBaiduEngine(true);
//    vr->getEnginePtr()->postRequest(audiopcm);
//}

int main()
{
//    TC_Log::setLogStatus(true);
//    VR_Module* vr = VR_Module::getInstance();
//    vr->Initialize();
//    vr->Start();

//    pthread_t id;
//    id = pthread_create(&id, nullptr, (void* (*)(void*))testPostAudio, vr);
//    while(1); BAC009S0764W0246.wav

    std::string url = "https://westus.stt.speech.microsoft.com/speech/recognition/dictation/cognitiveservices/v1";
    VR_CurlHttpTool cht;
    CurlMap header;
    header.insert(make_pair<string, string>("Transfer-Encoding", "chunked"));
    header.insert(make_pair<string, string>("Ocp-Apim-Subscription-Key", "e459325630614429b291adb42376d696"));
    header.insert(make_pair<string, string>("Content-type", "audio/wav; codec=audio/pcm; samplerate=16000"));

    CurlMap urlParam;
    urlParam.insert(make_pair<string, string>("language", "zh-cn"));
    urlParam.insert(make_pair<string, string>("format", "simple"));

    std::string response;

    cht.PostHttp(url, header, urlParam, &response, "/home/huyang/BAC009S0764W0246.wav");
    printf("response = %s\n", response.c_str());
}
