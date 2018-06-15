all: user

user: main.o account.o sqlite.o
	g++ -o user main.o account.o sqlite.o -lsqlite3 -lcrypto
main.o: main.cpp Account.hpp
	g++ -o main.o -c main.cpp
account.o: Account.cpp Account.hpp
	g++ -o account.o -c Account.cpp
sqlite.o: sqlite.cpp sqlite.hpp
	g++ -o sqlite.o -c sqlite.cpp
clean:
	rm main.o account.o sqlite.o
