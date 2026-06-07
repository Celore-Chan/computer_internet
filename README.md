# Socket Chat Room

基于 Socket 编程实现的双人实时聊天系统。

## 项目简介

本项目采用客户端-服务器（Client-Server）架构，使用 Socket 实现两台主机之间的实时通信。

用户可以通过客户端连接服务器，实现文本消息的实时收发。

## 功能实现

### 服务端

* Socket创建
* 端口绑定（Bind）
* 监听连接（Listen）
* 接收客户端连接（Accept）
* 消息转发

### 客户端

* 连接服务器
* 消息发送
* 消息接收
* 实时聊天

## 技术栈

* C/C++
* Socket Programming
* TCP/IP

## 项目结构

```text
.
├── server/
│   └── server.cpp
├── client/
│   └── client.cpp
└── README.md
```

## 运行环境

* Linux
* GCC / G++

## 编译

```bash
g++ server.cpp -o server
g++ client.cpp -o client
```

## 运行

启动服务端：

```bash
./server
```

启动客户端：

```bash
./client
```

## 项目核心

* TCP/IP通信机制
* Socket编程模型
* Client-Server架构设计
* 网络程序开发流程

## 后续优化方向

* 多用户聊天室
* 多线程处理客户端
* 用户登录认证
* 文件传输功能
* GUI聊天界面
* 群聊功能
