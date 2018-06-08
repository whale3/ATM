#include "account.hpp"
#include<iostream>
#include<string>
#include<sqlite3.h>
//验证
void AccountDAO::auth(const std::string& name,const std::string& password)
{
    const char* sql="select name from account"
                    " where name = ? and password = ? ";
    Sqlite_stmt stmt = db_.Prepare(sql);
    stmt.Bind(1,name.c_str());
    stmt.Bind(2,password.c_str());
    //抛出错误，匹配用户名和密码。
    if(stmt.Step()!=SQLITE_ROW)//select时用SQLITE_ROW
    {
        //std::cout<<stmt.Step()<<std::endl;
        std::cout<<"用户名或者密码错误"<<std::endl;
    }
    else 
    {
        std::cout<<"输入正确"<<std::endl;
    }
    
}
//注册
void AccountDAO::insert(const std::string& name,const std::string& password,double  balance)
{
    const char* sql="insert into Account(name,password,balance)"
                    " values(?,?,?)";
    Sqlite_stmt stmt = db_.Prepare(sql);
    stmt.Bind(1,name);
    stmt.Bind(2,password);
    stmt.Bind(3,balance);

    if(stmt.Step()==SQLITE_DONE)//insert,update时用SQLITE_DONE
    {
        std::cout<<"注册成功"<<std::endl;
    }
    else
    {
        std::cout<<"注册失败"<<std::endl;
    }
}
//存钱
void AccountDAO::deposit(const std::string& name,double sum)
{
    const char* sql="insert into log(name,operation) values(?,?)";
    const char* sql2="update account set balance = balance + ? where name = ?";
    Sqlite_stmt stmt1=db_.Prepare(sql);
    Sqlite_stmt stmt2=db_.Prepare(sql2);
    stmt1.Bind(1,name);
    stmt1.Bind(2,sum);

    stmt2.Bind(1,sum);
    stmt2.Bind(2,name);
    
    if(stmt1.Step()==SQLITE_DONE)
    {
        std::cout<<"存入成功(log)"<<std::endl;
    }
    else
    {
        std::cout<<"存入失败(log)"<<std::endl;
    }
    if(stmt2.Step()==SQLITE_DONE)
    {
        std::cout<<"存入成功(account)"<<std::endl;
    }
    else
    {
        std::cout<<"存入失败(account)"<<std::endl;
    }

}
//取钱
void AccountDAO::withdraw(const std::string& name,double sum)//传入的值都是+值
{
    const char* sql="insert into log(name,operation) values(?,?)";
    const char* sql2="update account set balance = balance - ? where name = ?";
    Sqlite_stmt stmt1=db_.Prepare(sql);
    Sqlite_stmt stmt2=db_.Prepare(sql2);
    stmt1.Bind(1,name);
    stmt1.Bind(2,-sum);//在log表里显示出负值。

    stmt2.Bind(1,sum);
    stmt2.Bind(2,name);
    if(stmt1.Step()==SQLITE_DONE)
    {
        std::cout<<"取钱成功(log)"<<std::endl;
    }
    else
    {
        std::cout<<"取钱失败(log)"<<std::endl;
    }
    if(stmt2.Step()==SQLITE_DONE)
    {
        std::cout<<"取钱成功(account)"<<std::endl;
    }
    else
    {
        std::cout<<"取钱失败(account)"<<std::endl;
    }

}
//转账
void AccountDAO::transfer(const std::string& name_from,const std::string& name_to,double sum)
{
    const char* sql="update account set balance = balance - ? where name = ?";
    const char* sql2="update account set balance = balance + ? where name = ?";
    const char* sql3="insert into log(name,operation) values(?,?)";

    Sqlite_stmt stmt1=db_.Prepare(sql);
    Sqlite_stmt stmt2=db_.Prepare(sql2);
    Sqlite_stmt stmt3=db_.Prepare(sql3);

    stmt1.Bind(1,-sum);
    stmt1.Bind(2,name_from);

    stmt2.Bind(1,sum);
    stmt2.Bind(2,name_to);

    stmt3.Bind(1,name_from);
    stmt3.Bind(2,-sum);
    if(stmt1.Step()==SQLITE_DONE)
    {
        std::cout<<"name_from转出成功(account)"<<std::endl;
    }
    else
    {
        std::cout<<"name_from转出失败(account)"<<std::endl;
    }
    if(stmt2.Step()==SQLITE_DONE)
    {
        std::cout<<"name_to进账成功(account)"<<std::endl;
    }
    else
    {
        std::cout<<"name_to进账失败(account)"<<std::endl;
    }
    if(stmt3.Step()==SQLITE_DONE)
    {
        std::cout<<"log表更新成功"<<std::endl;
    }
    else
    {
        std::cout<<"log表更新失败"<<std::endl;
    }
}
//查询
double AccountDAO::balance(const std::string& name)
{
    const char* sql="select name,balance from account where name = ?";
    Sqlite_stmt stmt=db_.Prepare(sql);

    stmt.Bind(1,name);
    while(stmt.Step()==SQLITE_ROW)
    {
        double val;
        stmt.Column(1,val);

        std::cout<<"balance:"<<val<<std::endl;
    }
}

