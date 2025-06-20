#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;


// UserService原来是一个本地服务，提供两个进程内的本地方法，Login和GetFriendLists
class UserService : public fixbug::UserServiceRpc
{
public: 
    bool Login(string name,string pwd)
    {
        cout<<"doing local service: Login"<<endl;
        cout<<"name:"<<name<<"pwd::"<<pwd<<endl;
        return true;        //不一定对
    }
    bool Register(uint32_t id, std::string name,string pwd)
    {
        cout<<"doing local service: Rigster"<<endl;
        cout<<"id: "<<id<<"name:"<<name<<" pwd:"<<pwd<<endl;
        return true;  
    }

    
    /*重写基类UserServicesRpc的虚函数，下面这些方法都是框架直接调用
    1. caller   ===>   Login(LoginRequest) =>muduo => callee
    2. callee  ===>   Login(LoginRequest) =>交到下面重写的Login方法
    */
    void Login(::google::protobuf::RpcController* controller,
                        const ::fixbug::LoginRequest* request,
                        ::fixbug::LoginResponse* response,
                        ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数LoginRequest，应用获取相应数据做本地业务
        string name = request->name();
        string pwd = request->pwd();

        //做本地业务
        bool login_result = Login(name,pwd);

        //把响应写入 包括错误码、错误消息、返回值
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg(" ");
        response->set_success(login_result);

        //执行回调操作
        done->Run();
    }

    void Register(::google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t id=request->id();
        string name=request->name();
        string pwd=request->pwd();

        bool  ret = Register(id,name,pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg(" ");
        response->set_success(ret);

        done->Run();
    }

};

int main(int argc, char **argv)
{
    //调用框架的初始化操作
    MprpcApplication::Init(argc,argv);

    //provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new UserService());

    //启动一个rpc服务发布节点   Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;
}