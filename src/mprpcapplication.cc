#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>

MprpcConfig MprpcApplication:: m_config;

void ShowArgcsHelp()
{
    std::cout<<"format: command -i <configfile>"<<std::endl;
    exit(EXIT_FAILURE);
}

void MprpcApplication:: Init(int argc, char **argv)
{
    if(argc<2)
    {
        ShowArgcsHelp();
        
    }
    int c = 0;
    std::string config_file;
    while((c = getopt(argc,argv, "i:")) !=-1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;
            break;
            
        case '?':

            ShowArgcsHelp();

        case ':':

            ShowArgcsHelp();
        
        default:
            break;
        }
    }
    //开始加载配置文件
    m_config.LoadConfigFile(config_file.c_str());

}

MprpcApplication& MprpcApplication:: GetInstance()
{
    static MprpcApplication app;
    return app;
}

MprpcConfig& MprpcApplication:: GetConfig()
{

    return m_config;
}