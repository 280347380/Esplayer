# Esplayer

一个基于C++的多进程通信和事件驱动的播放器项目。

## 项目特性

- **多进程架构**: 使用 `CProcess` 类实现进程间通信
- **事件驱动**: 基于 `CEpoll` 类的高性能事件处理
- **文件描述符传递**: 支持进程间文件描述符传递
- **模板化函数绑定**: 使用 `CFunction` 模板类进行函数绑定

## 项目结构

```
Esplayer/
├── main.cpp      # 主程序入口
├── Process.h     # 进程管理类
├── Function.h    # 函数绑定模板类
├── Epoll.h       # Epoll事件处理类
└── README.md     # 项目说明
```

## 核心组件

### CProcess 类
- 进程创建和管理
- 进程间通信 (IPC)
- 文件描述符传递
- 守护进程支持

### CEpoll 类
- 高性能事件监听
- 文件描述符管理
- 事件处理封装

### CFunction 类
- 模板化函数绑定
- 支持任意参数的函数调用
- 基于 std::bind 实现

## 编译和运行

```bash
# 编译
g++ -o esplayer main.cpp -std=c++11

# 运行
./esplayer
```

## 开发环境

- C++11 或更高版本
- Linux 系统 (支持 epoll)
- GCC 编译器

## 作者

wyh

## 许可证

MIT License