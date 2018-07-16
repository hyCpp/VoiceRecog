#ifndef CURLHTTP
#define CURLHTTP
#include <stdio.h>
#include <curl/curl.h>
#include <sstream>
#include <map>
#include <string.h>

enum postType
{
    public_post,
    multipart_post,
};

class CurlHttp
{
public:
    typedef std::map<std::string, std::string> CurlMap;
    CurlHttp();
    CurlHttp(const CurlHttp&) = delete;
    CurlHttp& operator = (const CurlHttp&) = delete;
    ~CurlHttp();
    int GetHttp(const std::string& url, CurlMap const* headers, CurlMap const* form, std::string *response);
    int PostHttp(const std::string& url, CurlMap const* headers, CurlMap const* form, std::string * response, postType type = public_post, const std::string& body = "");
    int PostHttp(const std::string& url, CurlMap const* headers, CurlMap const* form, std::string * response, const CurlMap& body, postType type = public_post);
    void setDebug(bool bug);
    void setTimeOut(int time);
    std::string getValueByKeyOfInput(const std::string& source, const std::string& key, const std::string &attrName = "") const;
    void getCookies(const std::string& source, std::string& target) const;
    std::string getHtmlContentTransforXml(const std::string& source, const std::string &key, const std::string &attrName) const;

private:
    void appendHeaders(CurlMap const & headers, curl_slist ** slist) const;
    void appendFormat(CurlMap const & formData , curl_httppost ** form, curl_httppost** last) const;
    std::string makeUrlParams(const CurlMap &params) const;

    bool m_debug;
    int m_timeout;
    CURL* curl;
};

#endif // CURLHTTP

