#include <iostream>
#include <string>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include <vector>
#include "logger.h"


using std::cout;
using std::cin;
using std::string;
using std::endl;


class FriendService : public fixbug::FriendServiceRpc
{
public:
    std::vector<string> GetFriendsList(uint32_t userid)
    {
        std::cout<<"DO GetFriendsList service! userid:"<<userid<<endl;
        std::vector<std::string> vec;
        vec.push_back("wang er");
        vec.push_back("ma zi");
        vec.push_back("liu yu");

        return vec;
    }
        void GetFriendsList(::google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendsListRequest* request,
                       ::fixbug::GetFriendsListResponse* response,
                       ::google::protobuf::Closure* done)
        {
            uint32_t userid = request->userid();
            std::vector<std::string>friendList = GetFriendsList(userid);
            response->mutable_result()->set_errcode(0);
            response->mutable_result()->set_errmsg("");
            for(std::string &name:friendList)
            {
                std::string *p = response->add_friends();
                *p = name;
            }
            done->Run();

        }

};

int main(int argc, char **argv)
{

    LOG_INFO("first log message!");
    LOG_ERR("%s:%s:%d",__FILE__,__FUNCTION__,__LINE__);
    //调用框架的初始化操作
    MprpcApplication::Init(argc,argv);

    //provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上
    RpcProvider provider;
    provider.NotifyService(new FriendService());

    //启动一个rpc服务发布节点   Run以后，进程进入阻塞状态，等待远程的rpc调用请求
    provider.Run();

    return 0;
}