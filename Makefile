CC=g++ 

INCLUDE_DIR=./include
SRC_DIR=./src
BIN_DIR=./bin

BIN=main
MAIN_BIN=$(BIN_DIR)/$(BIN)

CFLAGS=-Wall -Wextra -Wpedantic -g -O0 -std=c++17 -pthread -I$(INCLUDE_DIR)

all: $(MAIN_BIN)

$(BIN_DIR)/main: $(SRC_DIR)/*.cpp $(INCLUDE_DIR)/*.h
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/*.cpp 


run: $(MAIN_BIN)
	$(MAIN_BIN)

clean: 
	rm -rf $(BIN_DIR)/$(BIN)
