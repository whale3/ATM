#include <iostream>
#include <string>
#include <stdexcept>
#include <sqlite3.h>
#include "Account.hpp"

void Account::login(const std::string& name,const std::string& password)
{
    try{
        const char* sql="select name from Account where name=? and password=?";
        Sqlite_stmt stmt = db_.Prepare(sql);
        stmt.Bind(1,name);
        stmt.Bind(2,password);
        if(stmt.Step() != SQLITE_ROW)
             {
                 throw std::runtime_error("login error");
             }
       }
       catch(const std::runtime_error& e)
       {
            throw e;
       }
}

void Account::register_(const std::string& name, const std::string& password, double balance )
{
            const char* sql="insert into Account (name,password,balance) values(?,?,?)";
            Sqlite_stmt stmt=db_.Prepare(sql);
            stmt.Bind(1,name);
            stmt.Bind(2,password);
            stmt.Bind(3,balance);
            stmt.Step();
}
void Account::deposit(const std::string& name, double sum)
{
            const char* sql_1="insert into Log (name,operation) values(?,?)";
            const char* sql_2="update Account set balance = balance +? where name = ?";
            Sqlite_stmt stmt_1=db_.Prepare(sql_1);
            Sqlite_stmt stmt_2=db_.Prepare(sql_2);
            stmt_1.Bind(1,name);
            stmt_1.Bind(2,sum);
            stmt_2.Bind(1,sum);
            stmt_2.Bind(2,name);
            db_.Prepare("begin transaction").Step();
            stmt_1.Step();
        try{
            if(db_.Changes() != 1)
                {
                    std::cout<<"deposit failed"<<std::endl;
                    throw std::runtime_error("log update failed");
                }
            stmt_2.Step();
            if(db_.Changes() != 1)
                {
                    std::cout<<"deposit"<<std::endl;
                    throw std::runtime_error("deposit failed");
                }
           }
            catch(const std::runtime_error& e)
            {
                     db_.Prepare("rollback transaction").Step();
                     throw e;
            }
            db_.Prepare("commit transaction").Step();
}


void Account::withdraw(const std::string& name, double sum)
{
            const char* sql_1="insert into Log (name,operation) values(?,?)";
            const char* sql_2="update Account set balance = balance -? where name = ?";
            Sqlite_stmt stmt_1=db_.Prepare(sql_1);
            Sqlite_stmt stmt_2=db_.Prepare(sql_2);
            stmt_1.Bind(1,name);
            stmt_1.Bind(2,-sum);
            stmt_2.Bind(1,sum);
            stmt_2.Bind(2,name);
            db_.Prepare("begin transaction").Step();
            stmt_1.Step();
        try{
            if(db_.Changes() != 1)
                {
                    std::cout<<"withdraw failed"<<std::endl;
                    throw std::runtime_error("log update failed");
                }
            stmt_2.Step();
            if(db_.Changes() != 1)
                {
                    std::cout<<"withdraw"<<std::endl;
                    throw std::runtime_error("withdraw failed");
                }
           }
            catch(const std::runtime_error& e)
            {
                     db_.Prepare("rollback transaction").Step();
                     throw e;
            }
            db_.Prepare("commit transaction").Step();
}

void Account::transfer(const std::string& name_from, const std::string& to_name, double sum)
{
            const char* sql_1="insert into Log (name,operation) values(?,?)";
            const char* sql_2="insert into Log (name,operation) values(?,?)";
            const char* sql_3="update Account set balance = balance-? where name=?";
            const char* sql_4="update Account set balance = balance+? where name=?";

            Sqlite_stmt stmt_1=db_.Prepare(sql_1);
            Sqlite_stmt stmt_2=db_.Prepare(sql_2);
            Sqlite_stmt stmt_3=db_.Prepare(sql_3);
            Sqlite_stmt stmt_4=db_.Prepare(sql_4);

            stmt_1.Bind(1,name_from);
            stmt_1.Bind(2,-sum);
            stmt_2.Bind(1,to_name);
            stmt_2.Bind(2,sum);
            
            stmt_3.Bind(1,-sum);
            stmt_3.Bind(2,name_from);
            stmt_4.Bind(1,sum);
            stmt_4.Bind(2,to_name);
            try
           {
                     db_.Prepare("begin transaction").Step();
                     stmt_1.Step();
                     stmt_2.Step();
                     stmt_3.Step();
                     stmt_4.Step();
                 if(db_.Changes() != 4)
                     {
                        std::cout<<"transfer failed"<<std::endl;
                        throw std::runtime_error("transfer failed");
                     }
            }
            catch(const std::runtime_error& e)
            {
                     db_.Prepare("rollback transaction").Step();
                     throw e;
            }
            db_.Prepare("commit transaction").Step();
            
}

double Account::quary(const std::string& name)
{
            const char* sql="select name,balance from Account where name=?";
            Sqlite_stmt stmt=db_.Prepare(sql);
            stmt.Bind(1,name);
            double val=-1;
            if(stmt.Step()==SQLITE_ROW)
                 {
                    stmt.Column(1,val);
                 }
            else if(val=-1)
                 {
                     throw std::runtime_error("quary failed");
                 }
            return val;
} 
