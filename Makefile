all: ./out/build

./out/build: ./out/account_2.o ./out/account_1.o ./out/sqlite.o 
	g++ -o ./out/build ./out/account_2.o ./out/account_1.o ./out/sqlite.o  -lsqlite3 -lcrypto
./out/sqlite.o: ./src/sqlite.cc ./src/sqlite.hpp
	g++ -o ./out/sqlite.o -c ./src/sqlite.cc

#./out/sqlite_2.o: ./test/test.cc ./src/sqlite.hpp
#   g++ -o ./out/sqlite_2.o -c ./test/test.cc

./out/account_1.o: ./src/account.cc ./src/account.hpp 
	g++ -o ./out/account_1.o -c ./src/account.cc 
./out/account_2.o: ./test/account_test.cc ./src/account.hpp
	g++ -o ./out/account_2.o -c ./test/account_test.cc

#clean:
#	rm -f sqlite_1.o sqlite_2.o sqlite
