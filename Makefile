CC=g++ 

INCLUDE_DIR=./include
SRC_DIR=./src
BIN_DIR=./bin

BIN=main

CFLAGS=-Wall -Wextra -Wpedantic -g -O0 -std=c++17 -I$(INCLUDE_DIR)

all: $(BIN)

main: $(SRC_DIR)/*.cpp $(INCLUDE_DIR)/*.h
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $(SRC_DIR)/*.cpp 


run: 
	$(BIN_DIR)/$(BIN)

clean: 
	rm -rf $(BIN_DIR)/$(BIN)
