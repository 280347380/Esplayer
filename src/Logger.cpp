#include "../include/Logger.h"
#include <cstdio>      // asprintf / vasprintf
#include <cstdarg>     // va_list
#include <cstring>     // memcpy / memset
#include <sys/time.h>  // gettimeofday
#include <unistd.h>    // getpid
#include <pthread.h>   // pthread_self

/*
 * LogInfo 构造 / 析构
 */
LogInfo::LogInfo(const char* file, int line, const char* func,

                 pid_t pid, pthread_t tid, int level,
                 const char* fmt, ...)
    : bAuto(false)
{
    static const char* sLevel[] = {"INFO","DEBUG","WARNING","ERROR","FATAL"};
    char* head = nullptr;
    int   len  = asprintf(&head, "%s(%d):[%s][%s]<%d-%lu>(%s) ",
                          file, line, sLevel[level],
                          CLoggerServer::GetTimeStr().c_str(),
                          pid, (unsigned long)tid, func);
    if (len <= 0) return;
    if (head) {
        m_buf.assign(head);
        free(head);
    }

    va_list ap;
    va_start(ap, fmt);
    char* body = nullptr;
    len = vasprintf(&body, fmt, ap);
    va_end(ap);
    if (len > 0 && body) {
        m_buf.append(body);
        free(body);
    }
    m_buf += '\n';
}

LogInfo::LogInfo(const char* file, int line, const char* func,
                 pid_t pid, pthread_t tid, int level)
    : bAuto(true)
{
    static const char* sLevel[] = {"INFO","DEBUG","WARNING","ERROR","FATAL"};
    char* head = nullptr;
    int   len  = asprintf(&head, "%s(%d):[%s][%s]<%d-%lu>(%s) ",
                          file, line, sLevel[level],
                          CLoggerServer::GetTimeStr().c_str(),
                          pid, (unsigned long)tid, func);
    if (len > 0 && head) {
        m_buf.assign(head);
        free(head);
    }
}

LogInfo::LogInfo(const char* file, int line, const char* func,
                 pid_t pid, pthread_t tid, int level,
                 void* pData, size_t nSize)
    : bAuto(false)
{
    static const char* sLevel[] = {"INFO","DEBUG","WARNING","ERROR","FATAL"};
    char* head = nullptr;
    int   len  = asprintf(&head, "%s(%d):[%s][%s]<%d-%lu>(%s)\n",
                          file, line, sLevel[level],
                          CLoggerServer::GetTimeStr().c_str(),
                          pid, (unsigned long)tid, func);
    if (len <= 0) return;
    if (head) {
        m_buf.assign(head);
        free(head);
    }

    const unsigned char* data = reinterpret_cast<const unsigned char*>(pData);
    size_t i;
    for (i = 0; i < nSize; ++i) {
        char tmp[8];
        snprintf(tmp, sizeof(tmp), "%02X ", data[i]);
        m_buf += tmp;

        if ((i & 0x0F) == 0x0F) {                 // 每 16 字节加 ASCII
            m_buf += "\t; ";
            char ascii[17];
            size_t base = i - 15;
            for (size_t j = 0; j < 16; ++j) {
                unsigned char c = data[base + j];
                ascii[j] = (c >= 0x20 && c < 0x7F) ? static_cast<char>(c) : '.';
            }
            ascii[16] = '\0';
            m_buf += ascii;
            m_buf += '\n';
        }
    }
    // 处理尾部不足 16 字节部分
    size_t rem = i & 0x0F;
    if (rem) {
        for (size_t j = rem; j < 16; ++j) m_buf += "   ";
        m_buf += "\t; ";
        size_t base = i - rem;
        for (size_t j = 0; j < rem; ++j) {
            unsigned char c = data[base + j];
            m_buf += (c >= 0x20 && c < 0x7F) ? static_cast<char>(c) : '.';
        }
        m_buf += '\n';
    }
}

LogInfo::~LogInfo()
{
    if (bAuto) {
        m_buf += '\n';
        CLoggerServer::Trace(*this);
    }
}
