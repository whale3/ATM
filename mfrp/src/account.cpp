#include<iostream>
//#include "../src/account.hpp"
#include "account.hpp"
int main(int argc,char* argv[])
{

    Dbpath = argv[1];
//    Sqlite_db db(argv[1]);
    AccountDAO acc;
    //acc.auth(argv[2],argv[3]);//验证方法
    //acc.insert(argv[2],argv[3],200.00);//注册方法
    //acc.deposit(argv[2],4000.00);//存钱方法
    //acc.withdraw(argv[2],300.00);//取钱方法
    //acc.transfer(argv[2],argv[3],400.00);//转账方法
    acc.balance(argv[2]);//查询方法
    return 0;
    
}
