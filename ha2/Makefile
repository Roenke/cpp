BIN = ./bin/
SRC = ./src/
OBJS = \
	$(BIN)main.o \
	$(BIN)lint.o \
	$(BIN)mytests.o
TARGET = ./bin/lint
CXXFLAGS = -std=c++11 -Wall -g

all: bin build

run: build
	$(TARGET)

build: $(OBJS) 
	g++ $(OBJS) $(CXXFLAGS) -o $(TARGET)

$(BIN)%.o: $(SRC)%.cpp
	g++ -c $< $(CXXFLAGS) -o $@

bin:
	mkdir -p bin

clean:
	rm -r $(BIN)*
	rm $(TARGET)
	