#include "account.hpp"
#include<iostream>
#include<stdexcept>//抛出错误
#include<string>
#include<sqlite3.h>
#include "hash.cc"
//验证
void AccountDAO::auth(const std::string& name,const std::string& password)
{
    try{
         const char* sql="select name from account"
                         " where name = ? and password = ? ";
         Sqlite_stmt stmt = db_.Prepare(sql);
         
         std::string temp=sha256(password);
     
         stmt.Bind(1,name);
         //stmt.Bind(2,password.c_str());
         stmt.Bind(2,temp);
         //抛出错误，匹配用户名和密码。
     
//         db_.Prepare("begin transaction").Step();
         if(stmt.Step()!=SQLITE_ROW)//select时用SQLITE_ROW
         {
        //std::cout<<stmt.Step()<<std::endl;
                throw  std::runtime_error("！！");
         }
         } catch(const std::runtime_error& e) {
                throw e;
                }    
}
//注册
void AccountDAO::insert(const std::string& name,const std::string& password,double  balance)
{
   try{ 
        const char* sql="insert into Account(name,password,balance)"
                        " values(?,?,?)";
        Sqlite_stmt stmt = db_.Prepare(sql);
    
        std::string temp = sha256(password);
        
    
        stmt.Bind(1,name);
        //throw std::runtime_error("注册错误！!!!!!!!!!!!!!!!!!!!!");
        //stmt.Bind(2,password);
        stmt.Bind(2,temp);
        stmt.Bind(3,balance);
    
        stmt.Step();//insert,update时用SQLITE_DONE
   }catch(const std::runtime_error& e)
   {
        
        throw e;
   }
}
//存钱
void AccountDAO::deposit(const std::string& name,double sum)
{
    try {
        const char* sql="insert into log(name,operation) values(?,?)";
        const char* sql2="update account set balance = balance + ? where name = ?";
        Sqlite_stmt stmt1=db_.Prepare(sql);
        Sqlite_stmt stmt2=db_.Prepare(sql2);
        
        stmt1.Bind(1,name);
        stmt1.Bind(2,sum);
    
        stmt2.Bind(1,sum);
        stmt2.Bind(2,name);
        
        db_.Prepare("begin transaction").Step();
    
        stmt1.Step();
        if (db_.Changes() != 1)
        {
            std::cout<<"存入失败(account)"<<std::endl;
            throw  std::runtime_error("deposit insert log error");
        }

        stmt2.Step();
        if (db_.Changes() != 1)
        {
            std::cout<<"存入失败(account)"<<std::endl;
            throw  std::runtime_error("deposit update error");
        }
    } catch(const std::runtime_error& e) {
        db_.Prepare("rollback").Step();
        throw e;
    }

    db_.Prepare("commit").Step();
    //std::cout<<"存入成功(log)"<<std::endl;
}
//取钱
void AccountDAO::withdraw(const std::string& name,double sum)//传入的值都是+值
{
    try{
        const char* sql="insert into log(name,operation) values(?,?)";
        const char* sql2="update account set balance = balance - ? where name = ? and balance >= ?";
        Sqlite_stmt stmt1=db_.Prepare(sql);
        Sqlite_stmt stmt2=db_.Prepare(sql2);
        stmt1.Bind(1,name);
        stmt1.Bind(2,-sum);//在log表里显示出负值。

        stmt2.Bind(1,sum);
        stmt2.Bind(2,name);
        stmt2.Bind(3,sum);
        db_.Prepare("begin transaction").Step();
        stmt1.Step();
        if (db_.Changes()!=1)
        {
            std::cout<<"取钱失败(log)"<<std::endl;
            throw std::runtime_error("withdraw insert error");
        }
        stmt2.Step();
        if (db_.Changes() != 1)
        {
            std::cout<<"取钱失败(account)"<<std::endl;
            throw  std::runtime_error("withdraw update error");
        }
        }catch(const std::runtime_error& e) {
            db_.Prepare("rollback").Step();
            throw e;
             }   
    db_.Prepare("commit").Step();
    //std::cout<<"取钱成功(log)"<<std::endl;

}
//转账
void AccountDAO::transfer(const std::string& name_from,const std::string& name_to,double sum)
{
    try{
        const char* sql="update account set balance = balance - ? where name = ? and balance >= ? ";
        const char* sql2="update account set balance = balance + ? where name = ?";
        const char* sql3="insert into log(name,operation) values(?,?)";
    
        Sqlite_stmt stmt1=db_.Prepare(sql);
        Sqlite_stmt stmt2=db_.Prepare(sql2);
        Sqlite_stmt stmt3=db_.Prepare(sql3);
        Sqlite_stmt stmt4=db_.Prepare(sql3);
    
        stmt1.Bind(1,sum);
        stmt1.Bind(2,name_from);
        stmt1.Bind(3,sum);
    
        stmt2.Bind(1,sum);
        stmt2.Bind(2,name_to);
    
        stmt3.Bind(1,name_from);
        stmt3.Bind(2,-sum);
    
        stmt4.Bind(1,name_to);
        stmt4.Bind(2,sum);
        
        db_.Prepare("begin transaction").Step();
        stmt1.Step();
        if (db_.Changes()!=1)
        {
            throw std::runtime_error("transfer update(account_from) error");
        }
        stmt2.Step();
        if (db_.Changes()!=1)
        {
            throw std::runtime_error("transfer update(account_to) error");
        }
        stmt3.Step();
        if (db_.Changes()!=1)
        {
            std::cout<<"转出log记录失败"<<std::endl;
            throw std::runtime_error("transfer insert(log_from) error");
        }
        stmt4.Step();
        if (db_.Changes()!=1)
        {
            std::cout<<"转入log记录失败"<<std::endl;
            throw std::runtime_error("transfer insert(log_to) error");
        }
        } catch(const std::runtime_error& e) {
            db_.Prepare("rollback").Step();
            throw e;
             }   

    db_.Prepare("commit").Step();
    //std::cout<<"转账成功(log)"<<std::endl;
}
//查询
double AccountDAO::balance(const std::string& name)
{
       const char* sql="select name,balance from account where name = ?";
       Sqlite_stmt stmt=db_.Prepare(sql);
   
       double val = -1;

   try{ 
       stmt.Bind(1,name);
       if(stmt.Step()==SQLITE_ROW)
       {
           stmt.Column(1,val);
   
       }

       else
       if (val = -1)
       {
            throw std::runtime_error("search error");
        
       }
       }
       catch(const std::runtime_error& e) {
             std::cout<<"查询余额时错误"<<std::endl;
             }   

      
      /* 
      
       while(stmt.Step()==SQLITE_ROW)
       {
           stmt.Column(1,val);
       
        std::cout<<"balance:"<<val<<std::endl;
    }*/
    return val;
}

