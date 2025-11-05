#include "../include/Thread.h"

// 定义CThread的静态成员变量
std::map<pthread_t, CThread*> CThread::m_mapThread;
