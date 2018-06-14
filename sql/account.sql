create table account
(id integer primary key autoincrement not null,
name varchar(255) not null UNIQUE,
password varchar(64) not null,
balance double not null);
