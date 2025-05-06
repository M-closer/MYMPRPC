#include <iostream>
#include "mprpcapplication.h"
#include "friend.pb.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"

int main(int argc,char **argv)
{
    MprpcApplication::Init(argc,argv);

    // 远程调用发布的rpc方法
    fixbug::FriendServiceRpc_Stub stub(new MprpcChannel());

    fixbug::GetFriendsListRequest request;
    request.set_userid(1000);
    //rpc的响应
    fixbug::GetFriendsListResponse rsp;
    //发起rpc方法的调用
    MprpcController controller; //记录控制信息
    stub.GetFriendsList(&controller,&request,&rsp,nullptr);

    if(controller.Failed())
    {
        std::cout<< controller.ErrorText() <<std::endl;
    }
    else
    {
        if(rsp.result().errcode() == 0)
        {
            std::cout<<"rpc friend response success: "<<std::endl;
            for(int i=0;i<rsp.friends_size();i++)
            {
                std::cout<<"index: "<<i+1<< " name: "<<rsp.friends(i)<<std::endl;
            }
        }
        else
        {
            std::cout<<"rpc friend response error: "<<rsp.result().errmsg()<<std::endl;
        }
    }
}