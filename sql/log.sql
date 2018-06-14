create table log
(id integer primary key autoincrement not null,
name varchar(255) not null,
operation double not null,
date timestamp not null default(datetime('now','localtime')));
