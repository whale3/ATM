#ifndef Account_HPP
#define Account_HPP
#include <iostream>
#include <string>
#include <sqlite3.h>
#include "sqlite.hpp"

class Account
{
public:
        Account()=default;
        void login(const std::string& name, const std::string& password);
        void register_(const std::string& name, const std::string& password, double balance);
        void deposit(const std::string& name, double sum);
        void withdraw(const std::string& name, double sum);
        void transfer(const std::string& name_from,const std::string& to_name, double sum);
        double quary(const std::string& name);
private:
        Sqlite db_;
};

#endif
        
 
