#include "sqlite.hpp"
#include<iostream>
#include<string>
#include<sqlite3.h>

std::string Dbpath;

Sqlite_db:: Sqlite_db()
{
    sqlite3_open(Dbpath.c_str(),&db_);
}
int Sqlite_db::Changes()
{
    int ch;
    ch=sqlite3_changes(db_);
    return ch;
}
Sqlite_db::~Sqlite_db()
{
    sqlite3_close(db_);
    
}
Sqlite_stmt Sqlite_db::Prepare(const char* sql)//得到这条sql语句
{
    Sqlite_stmt stmt;
    if (sqlite3_prepare_v2(db_,sql,-1,&stmt.stmt_,NULL) != SQLITE_OK)
        throw std::runtime_error("sqlite3_prepare_v2() error");
    return stmt;
}
/*
Sqlite_stmt::Sqlite_stmt(Sqlite_db& db,const char* sql)
{
    sqlite3_prepare_v2(db.db_,sql,-1,&stmt_,NULL);

}*/
int Sqlite_stmt::Step()
{
    int rc=sqlite3_step(stmt_);
    if(rc!=SQLITE_ROW && rc!=SQLITE_DONE) {
        std::string msg = sqlite3_errstr(rc);
        throw std::runtime_error("step() error: " + msg);
    }
    
    return rc;


}
void Sqlite_stmt::Bind(int index,const char* val)
{
    sqlite3_bind_text(stmt_,index,val,-1,SQLITE_STATIC);    
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
void Sqlite_stmt:: Column(int i,int& val)
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

