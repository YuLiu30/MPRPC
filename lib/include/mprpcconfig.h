#pragma once

#include <unordered_map>
#include <string>

//rpcserverip  rpcserverport zookeeperip  zookeeperport
//框架读取配置文件类
class MprpcConfig
{
private:

    std::unordered_map<std::string, std::string>m_configMap;

public:
    //负责解析加载配置文件
    void LoadConfigFile(const char *config_file);

    //查询配置项信息
    std::string Load(const std::string &key);

    //去掉字符串前后空格
    void Trim(std::string &src_buf);

};

