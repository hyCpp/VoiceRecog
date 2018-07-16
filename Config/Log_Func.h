#ifndef LOG_FUNC_H
#define LOG_FUNC_H
#include <stdarg.h>
#include <stdio.h>
#define LOG_MAX_LENGTH 256
#define FC_LOG_TAG "Thread_Communication"
#define LOG_TAG_MODEL "VR"
#define LOGD(type, ...) {TC_Log p; p.output(type, __VA_ARGS__);}
#define LOG_DEBUG_FUNC_INOUT(tag)  Log_Func log((tag), (__PRETTY_FUNCTION__))
#define LOGD_FUNC() LOG_DEBUG_FUNC_INOUT(LOG_TAG_MODEL)
#define TCLOGD(...) {LOGD(__VA_ARGS__, "")}

class TC_Log
{
public:
    TC_Log()
    {

    }

    ~TC_Log()
    {

    }

    void output(char* formatStr, ...)
    {
        if (m_bLogStatus) {
            char str[LOG_MAX_LENGTH];
            va_list vArgList;
            va_start (vArgList, formatStr);
            vsprintf(str, formatStr, vArgList);
            va_end(vArgList);
            printf("%s\n", str);
        }
    }

    static void setLogStatus(bool status)
    {
        m_bLogStatus = status;
    }

    static bool getLogStatus()
    {
        return m_bLogStatus;
    }

private:
    TC_Log(const TC_Log& x);
    TC_Log& operator = (const TC_Log& x);

    static bool m_bLogStatus;
};

class Log_Func{
public:
    Log_Func(const char* tag, const char* func)
        : m_tag(tag)
        , m_func(func)
    {
         LOGD("[%s]  -> [%s]", m_tag, m_func);
    }

    ~Log_Func()
    {
        LOGD("[%s]  <- [%s]", m_tag, m_func);
    }

private:
    Log_Func(const Log_Func& a);
    Log_Func& operator = (const Log_Func& a);

    const char* m_tag;
    const char* m_func;
};

#endif // LOG_FUNC_H
