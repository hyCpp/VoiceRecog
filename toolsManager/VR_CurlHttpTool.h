/**
 * Copyright @ 2014 - 2017 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
/**
 * @file VR_CurlHttpTool.h
 * @brief Declaration file of class VR_CurlHttpTool.
 *
 * This file includes the declaration of class VR_CurlHttpTool.
 *
 * @attention used for C++ only.
 */

#ifndef VR_CURLHTTPTOOL
#define VR_CURLHTTPTOOL

#ifndef __cplusplus
#    error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif


/**
 * @brief The VR_CurlHttpTool class
 *
 * class declaration
 */

#include <stdio.h>
#include <curl/curl.h>
#include <sstream>
#include <map>
#include <string.h>

typedef std::map<std::string, std::string> CurlMap;


class VR_CurlHttpTool
{
public:
    VR_CurlHttpTool();
    VR_CurlHttpTool(const VR_CurlHttpTool&) = delete;
    VR_CurlHttpTool& operator = (const VR_CurlHttpTool&) = delete;
    ~VR_CurlHttpTool();

    int GetHttp(std::string url, const CurlMap& headers, const CurlMap& urlParams, std::string *response);
    int PostHttp(std::string url, const CurlMap& headers, const CurlMap& urlParams, std::string* response, const std::string& body = "");
//    int PostHttp(std::string url, const CurlMap& headers, const CurlMap& urlParams, std::string* response, const CurlMap& body);
    void setDebug(bool bug);
    void setTimeOut(int time);

private:
    void appendHeaders(const CurlMap& headers, curl_slist** slist) const;
    void appendFormat(const CurlMap& formData , curl_httppost** form, curl_httppost** last) const;
    void appendUrlParams(const CurlMap& params, std::string* url) const;
    std::string makeUrlParams(const CurlMap &params) const;

    bool m_debug;
    int m_timeout;
};

#endif // VR_CURLHTTPTOOL

