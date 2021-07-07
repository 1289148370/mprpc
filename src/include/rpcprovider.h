#pragma once
#include "google/protobuf/service.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <string>
#include "mprpcapplication.h"
#include <functional>
#include "google/protobuf/descriptor.h"
#include <unordered_map>

//框架提供的专门发布rpc服务的网络对象
class RpcProvider
{
public:
    //这里是框架提供给外部使用的，可以发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service *service);
    //启动rpc服务，开始提供rpc远程网络调用服务
    void Run();

private:
    //组合了TCP Server,只在Run中访问，写成run的局部方法
    //std::unique_ptr<muduo::net::TcpServer> m_tcpserverPtr;

    //组合EcentLoop
    muduo::net::EventLoop m_eventLoop;

    //service服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service;                                                    //保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor *> m_methodMap; //保存服务方法
    };
    //存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;
    //新的socket连接回调
    void onConnection(const muduo::net::TcpConnectionPtr &);
    //已建立连接用户的读写事件回调
    void onMessage(const muduo::net::TcpConnectionPtr &, muduo::net::Buffer *, muduo::Timestamp);

    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr &, google::protobuf::Message *);
};