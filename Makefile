CC=g++ -std=c++17

OPTIMIZATION=-O0

INCLUDE_DIR=./include
SRC_DIR=./src
SRC_SHARED_DIR=./src/shared
OBJ_DIR=./obj
BIN_DIR=./bin

OBJ_FILES=$(OBJ_DIR)/trie.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/indexing.o

BIN=main
MAIN_BIN=$(BIN_DIR)/$(BIN)

INCLUDE_DIR_FLAGS=-I$(INCLUDE_DIR)
LINKER_FLAGS=-pthread -lboost_system -lboost_date_time -lboost_filesystem

CFLAGS=-Wall -Wextra -Wpedantic -g $(OPTIMIZATION) $(LINKER_FLAGS) $(INCLUDE_DIR_FLAGS)

all: $(MAIN_BIN)

objs: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_SHARED_DIR)/%.cpp $(INCLUDE_DIR)/*.h
	$(CC) -o $@ $(CFLAGS) -c $<

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp objs 
	$(CC) -o $@ $(CFLAGS) $< $(OBJ_FILES)   

test: $(BIN_DIR)/test

clean: 
	rm $(BIN_DIR)/* $(OBJ_DIR)/*.o 
