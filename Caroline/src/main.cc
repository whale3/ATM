#include<iostream>
#include<string.h>
#include"account.hpp"


struct Info
{
    std::string Name;//用户名
    std::string Passwd;//密码
    double Balance;//余额
};
class User
{
public:
    void Menu1();//菜单1是登陆注册页面
    void Menu2(const std::string& username);//菜单2是操作界面
    void Login();//登陆
    void Sign_up();//注册
    void Query(const std::string& username);//查询
    void Deposit(const std::string& username);//存钱
    void Withdraw(const std::string& username);//取钱
    void Transfer(const std::string& username);//转账


};
void User::Menu1()
{
    std::string choose;
    while(true)
    {
        system("clear");
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"       小康银行自动存取款机"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"    1、登陆"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"    2、注册"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"    3、退出"<<std::endl;
        getline(std::cin,choose);
        if(choose=="1")
        {
            Login();
        }
        else if(choose=="2")
        {
            Sign_up();
        }
        else if(choose=="3")
        {
           return;
           //break; 
        }
    }
}
void User::Menu2(const std::string& username)
{
         while (true ) 
         {
    try{
         std::string choose;
         
             system("clear");
             std::cout<<std::endl;
             std::cout<<std::endl;
             std::cout<<"        小康银行欢迎您！"<<username<<std::endl;
             std::cout<<std::endl;
             std::cout<<"    1、查询"<<std::endl;
             std::cout<<std::endl;
             std::cout<<"    2、取钱"<<std::endl;
             std::cout<<std::endl;
             std::cout<<"    3、存钱"<<std::endl;
             std::cout<<std::endl;
             std::cout<<"    4、转账"<<std::endl;
             std::cout<<std::endl;
             std::cout<<"    5、退出"<<std::endl;
             getline(std::cin,choose);
             if(choose=="1")
             {
                 Query(username);
             }
             else if(choose=="2")
             {
                 Withdraw(username);
             }
             else if(choose=="3")
             {
                 Deposit(username);
             }
             else if(choose=="4")
             {
                 Transfer(username);
             }
             else if(choose=="5")
             {
                 return;
             }
             else 
             {
                 throw std::runtime_error("Menu2 error!");
             }
         
    }catch(const std::runtime_error& e)
    {
        std::cout<<e.what()<<"Menu2 catch error!!!"<<std::endl;

    }
    }
}
void User::Login()
{   
    AccountDAO a;
    Info info;
    int i;
    for(i=0; i<3;i++)
    { 
      try{
            system("clear");
            std::cout<<"请输入用户名： ";
            getline(std::cin,info.Name);
            std::cout<<"请输入密码： ";
            system("stty -echo");
            getline(std::cin,info.Passwd);
            system("stty echo");
            a.auth(info.Name,info.Passwd);
            break;
         }catch(const std::runtime_error& e) {
               std::cout<<std::endl<<"用户名或者密码错误，还有"<<2-i<<"次机会!"<< std::endl<<"继续输入按'y',按任意键返回上一级! "<<e.what()<<std::endl;
               std::string c;
               getline(std::cin,c);
               if(c=="y"|| c=="Y")
               {   
                   continue;//以下不执行了，从循环处开始执行
               }
               else
               {
                   return ;
               }
           }
   }
   if (i == 3)
       std::cout<<"请去柜台核实账号"<<std::endl;
   else
       Menu2(info.Name);
}
void User::Sign_up()
{   
    while(true)
    {
      try{
            AccountDAO a;
            Info info;
            std::string pwd;
            system("clear");
            std::cout<<"请输入用户名： ";
            getline(std::cin,info.Name);
            std::cout<<"请输入密码： ";
            system("stty -echo");
            getline(std::cin,info.Passwd);
            system("stty echo");
            std::cout<<std::endl<<"请再输入密码： ";
            system("stty -echo");
            getline(std::cin,pwd);
            system("stty echo");
            if(info.Name !="" && info.Passwd!="" && pwd!="")
            {
                if(info.Passwd==pwd)
                {
                   a.insert(info.Name,info.Passwd,0.0);
                   std::cout<<std::endl<<"注册成功！"<<std::endl<<"按任意键退出!"<<std::endl;
                   std::string c;
                   getline(std::cin,c);
                   return;
                }
                else
                {
                    std::cout<<std::endl<<"您两次输入的密码不一致，按任意键后请重新输入！不想输入那就按q退出吧！"<<std::endl;
                    std::string c;
                    getline(std::cin,c);
                    if(c=="q" || c=="Q")
                    {
                       return ;
                    }
                    continue;
                }
           }
           else
           {
               std::cout<<std::endl<<"您输入的用户名或密码为空，按任意键后请重新输入！不想输入了那就按q退出吧！"<<std::endl;
               std::string c;
               getline(std::cin,c);
               if(c=="q"||c=="Q")
               {
                   return ;
               }
               
           }
       }catch(const std::runtime_error& e){
               //std::cout<<e.what()<<std::endl;
               //    throw e;
             std::cout<<std::endl<<"您注册的用户名已经存在了，按任意键后请重新输入！不想注册了那就按q退出吧！"<<std::endl;
             std::string c;
             getline(std::cin,c);
             if(c=="q"||c=="Q")
             {
                 return ;
             }
        }
    }
}
void User::Query(const std::string& username)
{
    AccountDAO a;
    Info info;
    int sum;
    system("clear");
    sum = a.balance(username);
    std::cout<<"您还剩余额： "<<sum<<std::endl;
    std::cout<<"按任意键返回主菜单"<<std::endl;
    std::string c;
    getline(std::cin,c);

}
void User::Deposit(const std::string& username)
{
    while(true)
    {
          AccountDAO a;
          Info info;
          int money;
          std::string money_s;
          std::string c;
          system("clear");
          std::cout<<"注意！您只能输入整数，不能输入字符！"<<std::endl;
          std::cout<<"您输入的金额为： "<<std::endl;
          getline(std::cin,money_s);
          money=std::atoi(money_s.c_str());
          if(money>0)
          {
               std::cout<<"您存入的金额为："<<money<<std::endl;
               std::cout<<"确认请按'y',按任意键取消并返回上一个界面"<<std::endl;
               getline(std::cin,c);
               if(c=="y"||c=="Y")
               {       
                   a.deposit(username,money);
                   std::cout<<"存入成功！"<<std::endl;
                   std::cout<<"按任意键返回上一个界面"<<std::endl;
                   getline(std::cin,c);
                   return ;
               }
               else
               {
                   return ;
               }
          }     
          else
          {
              std::cout<<"您输入的金额有误，按任意键后再重新输入！不想输入按'q'!"<<std::endl;
              std::string c;
              getline(std::cin,c);
              if(c=="q"||c=="Q")
              {
                  return ;
              }
              continue;
          }
     }
}
void User::Withdraw(const std::string& username)
{
     AccountDAO a;
     Info info;
     int money;
     std::string money_s;
     std::string c;
     while(true)
     {
         try{
               system("clear");

               std::cout<<"注意！您只能输入整数，不能输入字符！"<<std::endl;
               std::cout<<"您输入的金额为： "<<std::endl;
               getline(std::cin,money_s);
               money=std::atoi(money_s.c_str());
               if(money>0)
               {
                     std::cout<<"您取出的金额为："<<money<<std::endl;
                     std::cout<<"确认请按'y',按任意键取消并返回上一个界面"<<std::endl;
                     getline(std::cin,c);
                     if(c=="y"||c=="Y")
                     {       
                        a.withdraw(username,money);
                        std::cout<<"取出成功！"<<std::endl;
                        std::cout<<"按任意键返回上一个界面"<<std::endl;
                        getline(std::cin,c);
                        return ;
                     }
                     else 
                     {
                        return ;
                     }
                    }
              else
              {
                   std::cout<<"您输入的金额有误，按任意键后再重新输入！不想输入按'q'"<<std::endl;
                   std::string c;
                   getline(std::cin,c);
                   if(c=="q"||c=="Q")
                   {
                        return ;
                   }
                   continue;
              }
            }catch(const std::runtime_error& e){
                  std::cout<<"您要取出的金额超过您的余额，请按任意键之后再进行重新输入取出金额!"<<std::endl;
                  //std::cout<<e.what()<<std::endl;
                  getline(std::cin,c);
                  continue;
                  }
                  
       }
}
void User::Transfer(const std::string& username)
{
    AccountDAO a;
    Info info;
    int money;
    std::string money_s;
    std::string c;
    std::string name_to;
    while(true)
    {
        try
        {
             system("clear");
             std::cout<<"注意！您只能输入整数，不能输入字符！"<<std::endl;
             std::cout<<"您要转入的账号是： "<<std::endl;
             getline(std::cin,name_to);
             std::cout<<"您要转出的金额是： "<<std::endl;
             getline(std::cin,money_s);
             money=std::atoi(money_s.c_str());//将string 转换成int型
             std::cout<<"您要转入的账号是："<<name_to<<std::endl<<"您要转出的金额是："<<money<<std::endl<<"确认请按'y',按任意键取消并返回上一个页面！"<<std::endl;
             getline(std::cin,c);
             if(c=="y"||c=="Y")
             {
                 a.transfer(username,name_to,money);
             }
             else
             {
                  return ;
             }
             std::cout<<"转出成功！"<<std::endl;
             std::cout<<"按任意键取消并返回上一个页面！"<<std::endl;
             getline(std::cin,c);
             return;
             
         }catch(const std::runtime_error& e){
               std::cout<<"您要转出的账号错误或金额超出您的余额，请按任意键之后再进行重新输入！："<<std::endl;
               //std::cout<<e.what()<<std::endl;
               getline(std::cin,c);
               continue;
              }
     }
}
int main(int argc,char* argv[])
{   
    Dbpath = "../mfrp.db";
    //Dbpath = argv[1];
    User user;
    user.Menu1();
    return 0;
}
