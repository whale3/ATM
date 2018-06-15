#include <sqlite3.h>
#include "sqlite.h"

namespace mfrp {

std::string DBFile = ":memory:";

SqlError::SqlError(int code, const char* fmt, ...) noexcept
{
    const char* const last = msg_ + sizeof(msg_);
    char* p = msg_;

    va_list args;
    va_start(args, fmt);
    p = Vslprintf(p, last, fmt, args);
    va_end(args);

    p = Slprintf(p, last, " failed: %s", ::sqlite3_errstr(code));
}

Sqlite::Sqlite()
{
    int rc = ::sqlite3_open(DBFile.c_str(), &db_);
    if (rc != SQLITE_OK)
        throw SqlError(rc, "sqlite3_open(\"%s\")", DBFile.c_str());
}

SqStmt Sqlite::prepare(const std::string_view& sql)
{
    SqStmt stmt;

    int rc = ::sqlite3_prepare_v2(db_, sql.data(), sql.size(),
                                  &stmt.stmt_, nullptr);
    if (rc != SQLITE_OK)
        throw SqlError(rc, "sqlite3_prepare_v2(\"%s\")", sql.data());

    return stmt;
}

void Sqlite::exec(const std::string_view& sql)
{
    prepare(sql).step();
}

int Sqlite::changes()
{
    return ::sqlite3_changes(db_);
}

Sqlite::~Sqlite()
{
    ::sqlite3_close_v2(db_);
}

void SqStmt::bind(unsigned idx, int val)
{
    int rc = ::sqlite3_bind_int(stmt_, idx, val);
    if (rc != SQLITE_OK)
        throw SqlError(rc, "sqlite3_bind_int(%d)", val);
}

void SqStmt::bind(unsigned idx, long val)
{
    int rc = ::sqlite3_bind_int64(stmt_, idx, val);
    if (rc != SQLITE_OK)
        throw SqlError(rc, "sqlite3_bind_int64(%ld)", val);
}

void SqStmt::bind(unsigned idx, const std::string_view& val, void(*dtor)(void*))
{
    int rc = ::sqlite3_bind_text(stmt_, idx, val.data(), val.size(), dtor);
    if (rc != SQLITE_OK)
        throw SqlError(rc, "sqlite3_bind_text(\"%s\")", val.data());
}

int SqStmt::step()
{
    int rc = ::sqlite3_step(stmt_);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE)
        throw SqlError(rc, "sqlite3_step()");
    return rc;
}

void SqStmt::column(unsigned idx, std::string& val)
{
    val = (const char *) ::sqlite3_column_text(stmt_, idx);
}

void SqStmt::column(unsigned idx, long& val)
{
    val = ::sqlite3_column_int64(stmt_, idx);
}

SqStmt::~SqStmt()
{
    ::sqlite3_finalize(stmt_);
}

}
