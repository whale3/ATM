#include <iostream>
#include <string>
#include <sqlite3.h>
#include "sqlite.hpp"

std::string DbFile;

Sqlite::Sqlite()
{
    sqlite3_open(DbFile.c_str(),&db_);
}

int Sqlite::Changes()
{
    int c;
    c=sqlite3_changes(db_);
    return c;
}

Sqlite::~Sqlite()
{
    sqlite3_close(db_);
}

Sqlite_stmt Sqlite::Prepare(const char* sql)
{
    Sqlite_stmt stmt;
    if(sqlite3_prepare_v2(db_,sql,-1,&stmt.stmt_,NULL) != SQLITE_OK)
        throw std::runtime_error("sqlite3_prepare_v2 error");
    return stmt;
}

int Sqlite_stmt::Step()
{
    int rc=sqlite3_step(stmt_);
    if(rc != SQLITE_ROW && rc != SQLITE_DONE)
    {
        std::string msg = sqlite3_errstr(rc);
        throw std::runtime_error("step error");
    }
    return rc;

}

void Sqlite_stmt::Bind(int index,int val)
{
    sqlite3_bind_int(stmt_,index,val);
}

void Sqlite_stmt::Bind(int index,double val)
{
    sqlite3_bind_double(stmt_,index,val);
}

void Sqlite_stmt::Bind(int index,const std::string& val)
{
    sqlite3_bind_text(stmt_,index,val.c_str(),-1,SQLITE_STATIC);
}

void Sqlite_stmt::Column(int i,std::string& val)
{
    val=(const char*) sqlite3_column_text(stmt_,i);
}

void Sqlite_stmt::Column(int i,int& val)
{
    val=sqlite3_column_int(stmt_,i);
}
void Sqlite_stmt::Column(int i,double& val)
{
    val=sqlite3_column_double(stmt_,i);
}

Sqlite_stmt::~Sqlite_stmt()
{
    sqlite3_finalize(stmt_);
}
