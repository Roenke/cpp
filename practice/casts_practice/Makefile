
CXXFLAGS=-O2 -DNDEBUG -fno-omit-frame-pointer -D_NDEBUG -Wall -Werror -pedantic -Wno-long-long -std=c++1y
BIN=./bin/
SOURCE=./src/

OBJS = \
	$(BIN)/encoded_reader.o \
	$(BIN)/encoded_writer.o \
	$(BIN)/executor.o       \
	$(BIN)/huffman_tree.o   \
	$(BIN)/io_exception.o   \
	$(BIN)/parameters_praser.o \
	$(BIN)/parse_exception.o   \
	$(BIN)/raw_reader.o     \
	$(BIN)/raw_writer.o     \
	$(BIN)/reader.o         \
	$(BIN)/task_descroptor.o   \
	$(BIN)/writer.o            \
	$(BIN)/main.o

CXX=g++

all: huffman
	echo "Complete"

huffman: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BIN)/huffman

$(BIN)/%.o: $(SOURCE)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm ./bin/*

.PHONY: clean all