CC=g++ 

INCLUDE_DIR=./include
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

OBJ_FILES=$(OBJ_DIR)/main.o $(OBJ_DIR)/trie.o $(OBJ_DIR)/utils.o

BIN=main
MAIN_BIN=$(BIN_DIR)/$(BIN)

INCLUDE_DIR_FLAGS=-I$(INCLUDE_DIR)
LINKER_FLAGS=-pthread -lboost_system -lboost_date_time -lboost_filesystem

CFLAGS=-Wall -Wextra -Wpedantic -g -O0 -std=c++17 $(LINKER_FLAGS) $(INCLUDE_DIR_FLAGS)

all: $(MAIN_BIN)

objs: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/main: objs 
	$(CC) $(CFLAGS) -o $@ $(OBJ_DIR)/*.o 


run: $(MAIN_BIN)
	$(MAIN_BIN)

clean: 
	rm -rf $(BIN_DIR)/$(BIN) $(OBJ_DIR)/*.o 
