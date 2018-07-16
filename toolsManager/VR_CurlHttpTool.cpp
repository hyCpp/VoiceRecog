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
 * @file VR_CurlHttpTool.cpp
 * @brief Implementation of class VR_CurlHttpTool
 */

#include "VR_CurlHttpTool.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
inline size_t onWriteData(void * buffer, size_t size, size_t nmemb, void * userp)
{
    std::string * str = dynamic_cast<std::string *>((std::string *)userp);
    str->append((char *)buffer, size * nmemb);
    return nmemb;
}

VR_CurlHttpTool::VR_CurlHttpTool()
    : m_debug(false)
    , m_timeout(10000)
{
}

VR_CurlHttpTool::~VR_CurlHttpTool()
{
}

void VR_CurlHttpTool::setDebug(bool bug)
{
    m_debug = bug;
}

void VR_CurlHttpTool::setTimeOut(int time)
{
    m_timeout = time;
}

int VR_CurlHttpTool::GetHttp(std::string url, const CurlMap &headers, const CurlMap& urlParams, std::string *response)
{
    CURL* curl = curl_easy_init();
    struct curl_slist * slist = nullptr;

    if (!headers.empty()) {
        this->appendHeaders(headers, &slist);
    }
    if (!urlParams.empty()) {
        this->appendUrlParams(urlParams, &url);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) response);

    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, true);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, this->m_timeout);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, this->m_debug);

    int status_code = curl_easy_perform(curl);

    curl_slist_free_all(slist);
    curl_easy_cleanup(curl);

    return status_code;
}

int VR_CurlHttpTool::PostHttp(std::string url, const CurlMap& headers, const CurlMap& urlParams, std::string *response, const std::string& body)
{
    CURL* curl = curl_easy_init();
    struct curl_slist * slist = nullptr;

    if (!headers.empty()) {
        this->appendHeaders(headers, &slist);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
    }
    if (!urlParams.empty()) {
        this->appendUrlParams(urlParams, &url);
    }
    if (!body.empty()) {
        struct stat file_info;
        stat(body.c_str(), &file_info);
        long fileSize = file_info.st_size;

        FILE* fp = fopen(body.c_str(), "rb");
        if (fp == nullptr) {
            fclose(fp);
            return -1;
        }

        char* postContent = (char*)malloc(fileSize);
        if (postContent == nullptr) {
            fclose(fp);
            return -1;
        }
        int readCount = fread(postContent, 1, fileSize, fp);
        if (readCount != fileSize) {
            fclose(fp);
            free(postContent);
            return -1;
        }
        curl_easy_setopt(curl, CURLOPT_POST, true);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postContent);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fileSize);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADER, true);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, onWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) response);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, true);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, this->m_timeout);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, this->m_debug);

    int status_code = curl_easy_perform(curl);

    curl_slist_free_all(slist);
    curl_easy_cleanup(curl);

    return status_code;
}

//int VR_CurlHttpTool::PostHttp(std::string url, const CurlMap& headers, const CurlMap& urlParams, std::string *response, const CurlMap &body)
//{
//    std::string _body = this->makeUrlParams(body);
//    return this->PostHttp(url, headers, urlParams, response, _body);
//}

std::string VR_CurlHttpTool::makeUrlParams(const CurlMap &params) const
{
    std::string body("");
    std::map<std::string, std::string>::const_iterator it;
    for (it = params.begin(); it != params.end(); ++it) {
        char* key = curl_escape(it->first.c_str(), (int) it->first.size());
        char* value = curl_escape(it->second.c_str(), (int) it->second.size());
        body.append(key);
        body.append("=");
        body.append(value);
        body.append("&");
        curl_free(key);
        curl_free(value);
    }

    return body;
}

void VR_CurlHttpTool::appendUrlParams(const CurlMap &params, std::string *url) const
{
    if(params.empty()) {
        return;
    }

    std::string content;
    content = this->makeUrlParams(params);
    bool url_has_param = false;
    for (const auto& ch : *url) {
        if (ch == '?') {
            url_has_param = true;
            break;
        }
    }
    if (url_has_param) {
        url->append("&");
    } else {
        url->append("?");
    }
    url->append(content);
}

void VR_CurlHttpTool::appendHeaders(const CurlMap &headers, curl_slist **slist) const
{
    std::ostringstream os;
    std::map<std::string, std::string>::const_iterator it;
    for (it = headers.begin(); it != headers.end(); ++it) {
        os << it->first << ":" << it->second;
        *slist = curl_slist_append(*slist, os.str().c_str());
        os.str("");
    }
}

void VR_CurlHttpTool::appendFormat(const CurlMap &formData, curl_httppost **form, curl_httppost **last) const
{
    std::map<std::string, std::string>::const_iterator it;
    for (it = formData.begin(); it != formData.end(); ++it) {
        curl_formadd(form, last, CURLFORM_COPYNAME, (it->first).c_str(), CURLFORM_COPYCONTENTS, (it->second).c_str(), CURLFORM_END);
    }
}
