#include <iostream>
#include <string>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include "logger.h"
#include <vector>

class FriendService : public fixbug::FriendServiceRpc
{
public:
    std::vector<std::string> GetFriendsList(uint32_t userid)
    {
        std::cout<<"do GetFriendsList service! userid: "<<userid <<std::endl;
        std::vector<std::string> vec;
        vec.push_back("mxh");
        vec.push_back("fyw");
        vec.push_back("gxl");
        return vec;
    }

    /*重写基类UserServiceRpc的虚函数，下面这些方法都是由框架直接调用的*/
    void GetFriendsList(::google::protobuf::RpcController* controller,
        const ::fixbug::GetFriendsListRequest* request,
        ::fixbug::GetFriendsListResponse* response,
        ::google::protobuf::Closure* done)
        {
            uint32_t userid = request->userid();

            std::vector<std::string> friendlist = GetFriendsList(userid);

            fixbug::ResultCode *code = response->mutable_result();
            code->set_errcode(0);
            code->set_errmsg("");
            for(std::string &name : friendlist)
            {
                std::string *p = response->add_friends();
                *p = name;
            }
            done->Run();
        }
private:
};

int main(int argc,char **argv)
{
    LOG_ERR("%s:%s:%d",__FILE__,__FUNCTION__,__LINE__);
    LOG_INFO("first log message!");


    MprpcApplication::Init(argc,argv);

    RpcProvider provider;
    provider.NofityService(new FriendService());

    provider.Run();
    return 0;
}