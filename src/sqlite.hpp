#ifndef _sqlite_hpp
#define _sqlite_hpp
#include<iostream>
#include<sqlite3.h>
#include<string>

extern std::string Dbpath;

class Sqlite_stmt;

class Sqlite_db
{
    
private:
    sqlite3 *db_=nullptr;
public:
    Sqlite_db();
    Sqlite_stmt Prepare(const char* sql);
    int Changes();
    
    ~Sqlite_db();
};

class  Sqlite_stmt
{
    friend class Sqlite_db;
private:
    sqlite3_stmt *stmt_;
public:
    // Sqlite_stmt(Sqlite_db& db,const char*sql);
     int Step();
     void Bind(int index,const char* val);
     void Bind(int index,int val);
     void Bind(int index,double val);
     void Bind(int index,const std::string& val);

     void Column(int i,std::string& val);
     void Column(int i,int& val);
     void Column(int i,double& val);
     ~Sqlite_stmt();
};

#endif
