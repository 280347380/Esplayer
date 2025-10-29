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
├── include/          # 头文件目录
│   ├── Process.h     # 进程管理类
│   ├── Function.h    # 函数绑定模板类
│   └── Epoll.h       # Epoll事件处理类
├── src/              # 源代码目录
│   └── main.cpp      # 主程序入口
├── docs/             # 文档目录
│   └── API.md        # API文档
├── build/            # 编译输出目录（自动生成）
├── bin/              # 可执行文件目录（自动生成）
├── Makefile          # 构建配置文件
├── .gitignore        # Git忽略文件配置
└── README.md         # 项目说明
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

### 使用 Makefile（推荐）

```bash
# 编译项目
make

# 运行程序
make run

# 清理编译文件
make clean

# 重新编译
make rebuild

# 查看帮助
make help
```

### 手动编译

```bash
# 编译
g++ -o bin/esplayer src/main.cpp -Iinclude -std=c++11

# 运行
./bin/esplayer
```

## 开发环境

- C++11 或更高版本
- Linux 系统 (支持 epoll)
- GCC 编译器

## 作者

wyh

## 许可证

MIT License