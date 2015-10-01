CXXFLAGS=-Werror -Wall
BIN=./bin/
SOURCE=./src/
CXX=g++
all: $(BIN)main.o $(BIN)mergesort.o 
	$(CXX) $(CXXFLAGS) $^ -o ./merge_sort
$(BIN)%.o: $(SOURCE)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm ./bin/*
.PHONY: clean all