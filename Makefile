CC=g++ 

INCLUDE_DIR=./include
SRC_DIR=./src
BIN_DIR=./bin

BIN=main
MAIN_BIN=$(BIN_DIR)/$(BIN)

INCLUDE_DIR_FLAGS=-I$(INCLUDE_DIR)
LINKER_FLAGS=-pthread -lboost_system -lboost_date_time

CFLAGS=-Wall -Wextra -Wpedantic -g -O0 -std=c++17 $(LINKER_FLAGS) $(INCLUDE_DIR_FLAGS)

all: $(MAIN_BIN)

$(BIN_DIR)/main: $(SRC_DIR)/*.cpp $(INCLUDE_DIR)/*.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/*.cpp 


run: $(MAIN_BIN)
	$(MAIN_BIN)

clean: 
	rm -rf $(BIN_DIR)/$(BIN)
