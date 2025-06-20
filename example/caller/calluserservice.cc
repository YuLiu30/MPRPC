#include <iostream>
#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc,char **argv)
{
    //整个程序启动以后，想使用mprpc框架享用rpc服务调用，必须初始化
    MprpcApplication::Init(argc,argv);

    //演示调用远程发不到rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    fixbug::LoginRequest request;
    //rpc方法的请求参数
    request.set_name("zhang san");
    request.set_pwd("123456");
    //rpc方法的响应
    fixbug::LoginResponse response;

    //发起rpc方法的调用
    stub.Login(nullptr,&request,&response,nullptr);//RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    //一次rpc调用完成，读调用结果
    if(response.result().errcode()==0)
    {
        std::cout<<"rpc Login response success:"<<response.success()<<std::endl;
    }
    else
    {
        std::cout<<"rpc login response error:"<<response.result().errmsg()<<std::endl;
        
    }

    fixbug::RegisterRequest req;
    req.set_id(2000);
    req.set_name("li si");
    req.set_pwd("666666");
    fixbug::RegisterResponse rsp;

    stub.Register(nullptr,&req,&rsp,nullptr);

    if(rsp.result().errcode()==0)
    {
        std::cout<<"rpc register response success:"<<rsp.success()<<std::endl;
    }
    else
    {
        std::cout<<"rpc register response error:"<<rsp.result().errmsg()<<std::endl;
        
    }


    return 0;
}