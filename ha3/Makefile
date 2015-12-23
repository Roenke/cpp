BIN = ./bin/
SRC = ./src/
OBJS = \
	$(BIN)any.o \
	$(BIN)test.o 
TARGET = ./bin/any
CXXFLAGS = -std=c++11 -Wall -g -O2

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
	