# Esplayer API 文档

## CProcess 类

进程管理类，提供进程创建、通信和文件描述符传递功能。

### 主要方法

#### `int SetEntryFunction(FUNCTYPE func)`
设置进程入口函数。

**参数:**
- `func`: 进程入口函数指针

**返回值:**
- 成功返回 0，失败返回 -1

#### `int CreateSubProcess()`
创建子进程。

**返回值:**
- 成功返回 0，失败返回 -1

#### `int SendFD(int fd)`
发送文件描述符到另一个进程。

**参数:**
- `fd`: 要发送的文件描述符

**返回值:**
- 成功返回 0，失败返回 -1

#### `int RecvFD(int& fd)`
接收来自另一个进程的文件描述符。

**参数:**
- `fd`: 接收到的文件描述符（引用）

**返回值:**
- 成功返回 0，失败返回 -1

---

## CEpoll 类

高性能事件处理类，封装了 Linux epoll 机制。

### 主要方法

#### `int Create(uint32_t maxevents)`
创建 epoll 实例。

**参数:**
- `maxevents`: 最大事件数量

**返回值:**
- 成功返回 0，失败返回 -1

#### `int Add(int fd, uint32_t events)`
添加文件描述符到 epoll 监听。

**参数:**
- `fd`: 文件描述符
- `events`: 监听的事件类型

**返回值:**
- 成功返回 0，失败返回 -1

#### `int WaitEvent(std::vector<EpollData>& events, int timeout = -1)`
等待事件发生。

**参数:**
- `events`: 事件容器（引用）
- `timeout`: 超时时间（毫秒），-1 表示无限等待

**返回值:**
- 返回发生的事件数量，失败返回 -1

---

## CFunction 类模板

函数绑定模板类，支持任意参数的函数调用。

### 主要方法

#### `CFunction(FUNCTION f, ARGS... args)`
构造函数，绑定函数和参数。

**参数:**
- `f`: 要绑定的函数
- `args`: 函数参数

#### `auto operator()()`
调用绑定的函数。

**返回值:**
- 返回绑定函数的执行结果