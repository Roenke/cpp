CPP_FLAGS=-Werror -Wall
BIN_PREFIX=./bin/
SRC_PREFIX=./src/
CC=g++
all: main.o command.o 
	$(CC) $(CPP_FLAGS) $(BIN_PREFIX)main.o $(BIN_PREFIX)command.o -o ./bot.out
main.o:
	$(CC) -c $(SRC_PREFIX)main.cpp -o $(BIN_PREFIX)main.o
command.o:
	$(CC) -c $(SRC_PREFIX)command.cpp -o $(BIN_PREFIX)command.o
clean:
	rm ./bin/*
.PHONY: clean all