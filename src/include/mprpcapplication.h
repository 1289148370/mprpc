#pragma once
#include "mprpcconfig.h"
#include "mprpccontroller.h"
#include "mprpcchannel.h"
//mprpc框架的基础类,不需要多个，单例模式，负责框架的初始化
class MprpcApplication
{
public:
    static void Init(int argc, char **argv);
    static MprpcApplication& GetInstance();
    static MprpcConfig& GetConfig();
private:
    static MprpcConfig m_config;
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
};