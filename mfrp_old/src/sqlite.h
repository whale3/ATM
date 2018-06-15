#ifndef _SQLITE_H
#define _SQLITE_H

#include "error.h"
#include <string>
#include <experimental/string_view>
namespace std { using experimental::string_view; }

struct sqlite3;
struct sqlite3_stmt;

namespace mfrp {

class SqStmt;

class SqlError : public Error {
public:
    SqlError(int code, const char* fmt, ...) noexcept;
};

class Sqlite {
public:
    Sqlite();

    Sqlite(const Sqlite&) = delete;
    Sqlite& operator=(const Sqlite&) = delete;

    SqStmt prepare(const std::string_view& sql);

    void exec(const std::string_view& sql);

    int changes();

    ~Sqlite();

private:
    ::sqlite3* db_ = nullptr;
};

class SqStmt {
    friend class Sqlite;

public:
    SqStmt() = default;
    SqStmt(SqStmt&&) = default;

    SqStmt(const SqStmt&) = delete;
    SqStmt& operator=(const SqStmt&) = delete;

    void bind(unsigned idx, int val);
    void bind(unsigned idx, long val);
    void bind(unsigned idx, const std::string_view& val, void(*dtor)(void*));

    int step();

    void column(unsigned idx, std::string& val);
    void column(unsigned idx, long& val);

    ~SqStmt();

private:
    ::sqlite3_stmt* stmt_ = nullptr;
};

extern std::string DBFile;

}

#endif
