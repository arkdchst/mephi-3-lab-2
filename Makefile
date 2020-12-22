.PHONY: all clean
.DEFAULT_GOAL := all

INCLUDE_DIR := include
SRC_DIR := src
BIN_DIR := bin

G++ := g++ -g -std=c++17 -Wall -I$(INCLUDE_DIR)

all: bin/test

bin/test: $(SRC_DIR)/test.cpp $(INCLUDE_DIR)/*
	mkdir -p $(BIN_DIR)
	
	$(G++) $(SRC_DIR)/test.cpp -o $(BIN_DIR)/test


clean:
	rm -rf bin/test