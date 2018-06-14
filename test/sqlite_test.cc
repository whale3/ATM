#include<iostream>
#include "../src/sqlite.hpp"

int main(int argc,char* argv[])
{
//   void sqlite3_prepare_v2(db_);

   Sqlite_db db;

   Sqlite_stmt st=db.Prepare(argv[1]);
   
   
   while(st.Step()==SQLITE_ROW)
   {
        int val;
        std::string val2;
        std::string val3;
        std::string val4;
        st.Column(0,val);
        st.Column(1,val2);
        st.Column(2,val3);
        st.Column(3,val4);

        std::cout<<val<<"   "<<val2<<"   "<<val3<<"   "<<val4<<"   "<<std::endl;
   }

  
 // Sqlite_stmt st(db, argv[2]);//方法2

  // stmt=db.sqlite3_prepare_v2(argv[2]);//方法1
   
    return 0;
}
