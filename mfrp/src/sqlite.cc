#include "sql.hpp"
#include<iostream>
#include<string>
#include<sqlite3.h>

Sqlite_db:: Sqlite_db(const std::string &db)
{
    sqlite3_open(db.c_str(),&db_);
}

Sqlite_db::~Sqlite_db()
{
    sqlite3_close(db_);
    
}
Sqlite_stmt::Sqlite_stmt(Sqlite_db& db,const char* sql)
{
    sqlite3_prepare_v2(db.db_,sql,-1,&stmt_,NULL);

}
int Sqlite_stmt :: Step()
{
    int rc=sqlite3_step(stmt_);
    if(rc!=SQLITE_ROW && rc!=SQLITE_DONE)
       std::cout<<"Error sqlite_step"<<std::endl;
    return rc;


}
void Sqlite_stmt::Column(int i,std::string& val)
     {
        val=(const char*) sqlite3_column_text(stmt_,i);
     }
void Sqlite_stmt:: Column(int i,int& val)
     {
        val=sqlite3_column_int(stmt_,i);
     }
Sqlite_stmt::~Sqlite_stmt()
     {
        sqlite3_finalize(stmt_);
     }

