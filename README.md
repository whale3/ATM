ATM Simulator<br>
====
用C++编写一个模拟自动存取款机（ATM）程序，实现基本的存取款及转账功能。控制台界面，使用SQLite文件数据库来保存用户数据。<br>

开发环境 <br>
------
操作系统：Linux Ubuntu 17.10<br>
C++编译器：g++ 7.2 / clang++ 5<br>
数据库：SQLite 3<br>
依赖库：libsqlite3, libcrypto（用于计算SHA-256）<br>

前端交互界面<br>
------
Console界面，屏幕显示命令菜单，用户通过键盘输入来选择运行对应的功能。<br>
功能点：清屏、检查用户输入、密码输入、数字输入、Ctrl-D处理<br>

数据库访问类的封装<br>
------
SQLite提供C API，要求学生使用C++的风格来封装原始的C API<br>

单元测试<br>
------
编写并运行简单的单元测试程序<br>

Makefile<br>
------
手动编写简单的Makefile文件来管理程序的编译<br>

功能列表：<br>
------
前端交互	清屏，输入检查，密码不回显，Ctrl D<br>
注册	存入hash后的密码<br>
登录	密码hash比较<br>
存款	日志<br>
取款	余额检查，事务控制，日志<br>
转账	余额检查，事务控制，日志<br>
查询余额	<br>


