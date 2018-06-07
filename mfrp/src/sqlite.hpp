ifndef _sql_hpp
#define _sql_hpp
#include<iostream>
#include<sqlite3.h>
#include<string>
class Sqlite_db
{
    friend class Sqlite_stmt;
private:
    sqlite3 *db_=nullptr;
public:
    Sqlite_db(const std::string &db);
    ~Sqlite_db();
};

class  Sqlite_stmt
{
private:
    sqlite3_stmt *stmt_;
public:
     Sqlite_stmt(Sqlite_db& db,const char*sql);
     int Step();
     void Column(int i,std::string& val);
     void Column(int i,int& val);
     ~Sqlite_stmt();
};

#endif
