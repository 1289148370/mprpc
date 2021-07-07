#include "test.pb.h"
#include <iostream>
#include <string>
using namespace std;
using namespace fixbug;
int main(){
    //普通成员变量，类对象成员变量，列表成员变量

    // LoginResponse rsp;
    // ResultCode *rc = rsp.mutable_result();//对于类里面成员变量是另一类，用mutable获取成员变量的一个指针
    // rc->set_errcode(1);
    // rc->set_errmsg("登陆处理失败了");

    GetFriendListReponse rsp;
    ResultCode *rc = rsp.mutable_result();
    rc->set_errcode(0);
    
    //User* GetFriendListReponse::add_friend_list() {} 返回一个要添加的好友指针
    User *user1 = rsp.add_friend_list();
    user1->set_name("zhangsan");
    user1->set_age(20);
    user1->set_sex(User::MAN);

    User *user2 = rsp.add_friend_list();
    user2->set_name("lisi");
    user2->set_age(22);
    user2->set_sex(User::MAN);

    std::cout << rsp.friend_list_size()<<std::endl;

    //fixbug::User* GetFriendListReponse::mutable_friend_list(int index) {
    //return friend_list_.Mutable(index);}访问列表成员
    //rsp.friend_list(1)
    return 0;
}


int main1(){
    //封装了login请求对象的数据
    LoginRequest req;
    req.set_name("zhangsan");
    req.set_pwd("123456");
    //对象数据序列化成string  .c_str字符串
    std::string send_str;//定义一个字符串
    if(req.SerializeToString(&send_str)){//吧对象req序列化成字符串传给send_str,成功返回true 
        cout<<send_str<<endl;
    }     
    
    //从send_str反序列化为一个login对象
    LoginRequest reqB;
    if(reqB.ParseFromString(send_str)){
        cout<<reqB.name()<<endl;
        cout<<reqB.pwd()<<endl;
    }
    return 0;
}