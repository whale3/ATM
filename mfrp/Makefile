
all: ./out/sqlite.o

./out/sqlite.o: ./out/sqlite_1.o ./out/sqlite_2.o
	g++ -o ./out/sqlite.o ./out/sqlite_1.o ./out/sqlite_2.o -lsqlite3
./out/sqlite_1.o: ./src/sqlite.cc ./src/sqlite.hpp
	g++ -o ./out/sqlite_1.o -c ./src/sqlite.cc
./out/sqlite_2.o: ./test/test.cpp ./src/sqlite.hpp
	g++ -o ./out/sqlite_2.o -c ./test/test.cpp

#clean:
#	rm -f sqlite_1.o sqlite_2.o sqlite
