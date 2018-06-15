#ifndef _account_hpp
#define _account_hpp
#include<iostream>
#include "sqlite.hpp"
#include<iostream>
#include<sqlite3.h>
#include<string>
class AccountDAO
{
private:
    Sqlite_db db_;

public:
    AccountDAO()=default;
    void auth(const std::string& name,const std::string& password);
    void insert(const std::string& name,const std::string& password,double balance);
    void deposit(const std::string& name,double sum);
    void withdraw(const std::string& name,double sum);
    void transfer(const std::string& name_from,const std::string& name_to,double sum);
    double balance(const std::string& name);
};


#endif
