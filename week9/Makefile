BIN = ./bin/
SRC = ./src/
OBJS = \
	$(BIN)main.o \
	$(BIN)my_stream_file.o \
	$(BIN)my_stream_con.o \
TARGET = ./my_streams
CXXFLAGS = -std=c++11

all: bin build

build: $(OBJS) 
	g++ $(OBJS) $(CXXFLAGS) -o $(TARGET)

$(BIN)%.o: $(SRC)%.cpp
	g++ -c $< $(CXXFLAGS) -o $@

bin:
	mkdir -p bin

clean:
	rm -r $(BIN)*
	rm $(TARGET)