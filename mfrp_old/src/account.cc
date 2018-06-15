#include <sqlite3.h>
#include "account.h"

namespace mfrp {

AccountError::AccountError(const char* fmt, ...) noexcept
{
    va_list args;
    va_start(args, fmt);
    std::vsnprintf(msg_, sizeof(msg_), fmt, args);
    va_end(args);
}

void AccountDAO::auth(const std::string& username, const std::string& password)
{
    const char* sql = "SELECT username FROM Account"
                      " WHERE username = ? AND password = ?";
    SqStmt stmt = sqlite_.prepare(sql);

    stmt.bind(1, username, SQLITE_STATIC);
    stmt.bind(2, password, SQLITE_STATIC);

    if (stmt.step() != SQLITE_ROW)
        throw AccountError("用户名或密码错误");
}

void AccountDAO::insert(const Account& account)
{
    const char* sql = "INSERT INTO Account(username, password, balance)"
                      " VALUES(?, ?, ?)";
    SqStmt stmt = sqlite_.prepare(sql);

    stmt.bind(1, account.username, SQLITE_STATIC);
    stmt.bind(2, account.password, SQLITE_STATIC);
    stmt.bind(3, account.balance);

    stmt.step();

    if (sqlite_.changes() != 1)
        throw AccountError("INSERT failure");
}

void AccountDAO::deposit(const std::string& username, long amount)
{
    deposit_(username, amount);

    log_(username, "deposit", amount);
}

void AccountDAO::deposit_(const std::string& username, long amount)
{
    const char* sql = "UPDATE Account SET balance = balance + ?"
                      " WHERE username = ?";
    SqStmt stmt = sqlite_.prepare(sql);

    stmt.bind(1, amount);
    stmt.bind(2, username, SQLITE_STATIC);

    stmt.step();

    if (sqlite_.changes() != 1)
        throw AccountError("DEPOSIT UPDATE failure");
}

void AccountDAO::withdraw(const std::string& username, long amount)
{
    try {
        sqlite_.exec("BEGIN IMMEDIATE TRANSACTION");

        if (balance(username) < amount)
            throw AccountError("余额不足");

        withdraw_(username, amount);

        log_(username, "withdraw", amount);

        sqlite_.exec("COMMIT TRANSACTION");

    } catch (const Error& e) {
        sqlite_.exec("ROLLBACK TRANSACTION");
        throw e;
    }
}

void AccountDAO::withdraw_(const std::string& username, long amount)
{
    const char* sql = "UPDATE Account SET balance = balance - ?"
                      " WHERE username = ?";
    SqStmt stmt = sqlite_.prepare(sql);

    stmt.bind(1, amount);
    stmt.bind(2, username, SQLITE_STATIC);

    stmt.step();

    if (sqlite_.changes() != 1)
        throw AccountError("WITHDRAW UPDATE failure");
}

void AccountDAO::transfer(const std::string& from, const std::string& to, long amount)
{
    try {
        sqlite_.exec("BEGIN IMMEDIATE TRANSACTION");

        if (balance(from) < amount)
            throw AccountError("余额不足");

        withdraw_(from, amount);

        log_(from, "transfer out", amount);

        deposit_(to, amount);

        log_(to, "transfer in", amount);

        sqlite_.exec("COMMIT TRANSACTION");

    } catch (const Error& e) {
        sqlite_.exec("ROLLBACK TRANSACTION");
        throw e;
    }
}

long AccountDAO::balance(const std::string& username)
{
    const char* sql = "SELECT balance FROM Account WHERE username = ?";
    SqStmt stmt = sqlite_.prepare(sql);

    stmt.bind(1, username, SQLITE_STATIC);

    long amount = 0;

    if (stmt.step() != SQLITE_ROW)
        throw AccountError("账户名错误");

    stmt.column(0, amount);

    return amount;
}

void AccountDAO::log_(const std::string& username,
                      const std::string_view& operation, long amount)
{
    const char* sql = "INSERT INTO Log(username, operation, amount)"
                      " VALUES(?, ?, ?)";
    SqStmt stmt = sqlite_.prepare(sql);

    stmt.bind(1, username, SQLITE_STATIC);
    stmt.bind(2, operation, SQLITE_STATIC);
    stmt.bind(3, amount);

    stmt.step();

    if (sqlite_.changes() != 1)
        throw AccountError("Log failure");
}

}
