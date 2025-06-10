#pragma once

//mprpc 框架的基础类,负责框架的初始化操作
#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

class  MprpcApplication
{
private:
    static MprpcConfig m_config;

    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;

public:
    static void Init(int argc, char **argv);
    static MprpcApplication& GetInstance();
    static MprpcConfig& GetConfig();
};

