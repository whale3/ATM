all: ./out/start

./out/start: ./out/main.o ./out/account.o ./out/sqlite.o 
	g++ -o ./out/start ./out/main.o ./out/account.o ./out/sqlite.o  -lsqlite3 -lcrypto
./out/sqlite.o: ./src/sqlite.cc ./src/sqlite.hpp
	g++ -o ./out/sqlite.o -c ./src/sqlite.cc
./out/account.o: ./src/account.cc ./src/account.hpp 
	g++ -o ./out/account.o -c ./src/account.cc 
./out/main.o: ./src/main.cc ./src/account.hpp
	g++ -o ./out/main.o -c ./src/main.cc
#clean:
#	rm -f sqlite_1.o sqlite_2.o sqlite
