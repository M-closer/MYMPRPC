#include<iostream>
#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc,char **argv)
{
    // 整个程序启动以后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架的初始化函数（只初始化一次）
    MprpcApplication::Init(argc,argv);

    // 演示调用远程发布的rpc方法Login
    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    // rpc方法请求参数
    fixbug::LoginRequest request;
    request.set_name("li si");
    request.set_pwd("123456");
    // rpc方法的响应
    fixbug::LoginResponse response;
    // 发起rpc方法的调用  同步的rpc调用过程   MprpcChannel::callmethod
    stub.Login(nullptr,&request,&response,nullptr);  //RpcChannel->RpcChannel::callMethod 集中来做所有rpc方法调用的参数序列化和网络发送

    // rpc调用完成，读调用的结果
    if(response.result().errcode() == 0)
    {
        std::cout<<"rpc login response success: "<<response.success()<<std::endl;
    }
    else
    {
        std::cout<<"rpc login response error: "<<response.result().errmsg()<<std::endl;
    }

    // rpc方法请求参数
    fixbug::RegisterRequest Register_request;
    Register_request.set_id(1000);
    Register_request.set_name("mxh");
    Register_request.set_pwd("666666");
    //rpc方法的响应
    fixbug::RegisterResponse Register_response;
    stub.Register(nullptr,&Register_request,&Register_response,nullptr);

    if(Register_response.result().errcode() == 0)
    {
        std::cout<<"rpc register response success: "<<response.success()<<std::endl;
    }
    else
    {
        std::cout<<"rpc register response error: "<<response.result().errmsg()<<std::endl;
    }

    return 0;
}