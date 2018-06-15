#ifndef sqlite_hpp
#define sqlite_hpp
#include <iostream>
#include <string>
#include <sqlite3.h>

extern std::string DbFile;

class Sqlite_stmt;

class Sqlite
{
public:
        Sqlite();
        Sqlite_stmt Prepare(const char* sql);
        int Changes();

        ~Sqlite();
private:
        sqlite3 *db_=nullptr;
};

class Sqlite_stmt
{
    friend class Sqlite;
public:
        int Step();
        void Bind(int index,const std::string& val);
        void Bind(int index,int val);
        void Bind(int index,double val);

        void Column(int i,std::string& val);
        void Column(int i,int& val);
        void Column(int i,double& val);
        ~Sqlite_stmt();
private:
        sqlite3_stmt *stmt_;
};


#endif
