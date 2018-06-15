#ifndef _ACCOUNT_H
#define _ACCOUNT_H

#include "sqlite.h"

namespace mfrp {

struct Account {
    std::string username;
    std::string password;
    long balance;
};

class AccountError : public Error {
public:
    explicit AccountError(const char* fmt, ...) noexcept;
};

class AccountDAO {
public:
    void auth(const std::string& username, const std::string& password);
    void insert(const Account& account);
    void deposit(const std::string& username, long amount);
    void withdraw(const std::string& username, long amount);
    void transfer(const std::string& from, const std::string& to, long amount);
    long balance(const std::string& username);

private:
    void deposit_(const std::string& username, long amount);
    void withdraw_(const std::string& username, long amount);
    void log_(const std::string& username, const std::string_view& operation, long amount);

    Sqlite sqlite_;
};

}

#endif
