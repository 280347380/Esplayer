#pragma once
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <cerrno>
#include <errno.h>
#include <signal.h>
#include <memory.h>
#define EVENT_SIZE 1024

class EpollData{
public:
    EpollData() {m_data.u64=0;}
    EpollData(void* ptr) {m_data.ptr=ptr;}
    explicit EpollData(int fd) {m_data.fd=fd;}
    explicit EpollData(uint32_t u32) {m_data.u32=u32;}
    explicit EpollData(uint64_t u64) {m_data.u64=u64;}
    EpollData(const EpollData& data) {m_data.u64=data.m_data.u64;}
    ~EpollData() = default;
public:
    EpollData& operator=(const EpollData& data) {
        if(this!=&data)
            m_data.u64=data.m_data.u64;
        return *this;
    }
    EpollData& operator=(void* ptr) {
        m_data.ptr=ptr;
        return *this;
    }
    EpollData& operator=(int fd) {
        m_data.fd=fd;
        return *this;
    }
    EpollData& operator=(uint32_t u32) {
        m_data.u32=u32;
        return *this;
    }
    EpollData& operator=(uint64_t u64) {
        m_data.u64=u64;
        return *this;
    }
    operator epoll_data_t&() { return m_data; }
    operator const epoll_data_t&()const { return m_data; }
    operator epoll_data_t*() { return &m_data; }
    operator const epoll_data_t*()const { return &m_data; }
private:
    epoll_data_t m_data;
};

using EPEvent = std::vector<epoll_event>;

class CEpoll
{
public:
    CEpoll(){
        m_epoll=-1;
    }
    ~CEpoll(){
        Close();
    }
    CEpoll(const CEpoll&) = delete;
    CEpoll& operator=(const CEpoll&) = delete;
public:
    // 操作符重载
    operator int() const { return m_epoll; }
    
    // 初始化epoll
    int Create(unsigned count){
        m_epoll=epoll_create(count);
        if(m_epoll == -1){
            return -1;
        }
        return 0;
    }
    
    //小于0表示错误，等于0表示没有事件发生，大于0表示成功拿到事件
    ssize_t WaitEvent(EPEvent& events,int timeout = 10){
        if(m_epoll==-1){
            return -1;
        }
        EPEvent evs(EVENT_SIZE);
        int ret = epoll_wait(m_epoll,evs.data(),(int)evs.size(),timeout);
        if(ret==-1){
            if((errno == EINTR)||(errno == EAGAIN)){
                return 0;
            }
            return -2;
        }
        if(ret>(int)evs.size()){
            evs.resize(ret);
        }
        memcpy(events.data(),evs.data(),sizeof(epoll_event)*ret);
        return ret;
    }

    // 添加文件描述符到epoll
    int Add(int fd, const EpollData& data, uint32_t events = EPOLLIN){
        if(m_epoll==-1){
            return -1;
        }
        epoll_event ev;
        ev.events=events;
        ev.data=data;
        int ret = epoll_ctl(m_epoll,EPOLL_CTL_ADD,fd,&ev);
        if(ret==-1){
            return -2;
        }
        return 0;
    }
    
    // 修改文件描述符的事件
    int Modify(int fd, uint32_t events,const EpollData& data=EpollData((void*)0)){
        if(m_epoll==-1){
            return -1;
        }
        epoll_event ev;
        ev.events=events;
        ev.data=data;
        int ret = epoll_ctl(m_epoll,EPOLL_CTL_MOD,fd,&ev);
        if(ret==-1){
            return -2;
        }
        return 0;
    }
    
    // 从epoll中删除文件描述符
    int Del(int fd){
        if(m_epoll==-1){
            return -1;
        }
        int ret = epoll_ctl(m_epoll,EPOLL_CTL_DEL,fd,NULL);
        if(ret==-1){
            return -2;
        }
        return 0;
    }
    
    
    // 获取事件数量
    //int GetEventCount() const;
    
    // 获取指定索引的事件
    //const epoll_event& GetEvent(int index) const;
    
    // 关闭epoll
    void Close(){
        if(m_epoll!=-1){
            int fd=m_epoll;
            m_epoll=-1;
            close(fd);
        }
    }

private:
    int m_epoll;
};