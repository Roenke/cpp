CXXFLAGS=-Werror -Wall
BIN=./bin/
SOURCE=./src/
CXX=g++
all: $(BIN)main.o $(BIN)command.o 
	$(CXX) $(CXXFLAGS) $^ -o ./bot.out
$(BIN)%.o: $(SOURCE)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm ./bin/* ./bot.out
.PHONY: clean all