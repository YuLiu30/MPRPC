#pragma once

#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>

//封装的zk客户端
class ZkClient
{
public:
    ZkClient();
    ~ZkClient();
    //在zkclient启动连接zkserver
    void Start();
    //根据指定路径创建znode
    void Create(const char *path, const char *data, int datalen, int state=0);
    //获取指定节点的内容
    std::string GetData(const char *path);
private:
    // 2k的客户端句柄
    zhandle_t *m_zhandle;
};