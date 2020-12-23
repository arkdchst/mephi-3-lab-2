.PHONY: all clean
.DEFAULT_GOAL := all

INCLUDE_DIR := include
SRC_DIR := src
BIN_DIR := bin

G++ := g++ -g -std=c++17 -Wall -Wno-reorder -Wno-sign-compare -I$(INCLUDE_DIR)

all: bin/index_ui bin/sparse_ui

bin/index_ui: $(SRC_DIR)/index_ui.cpp $(SRC_DIR)/index.cpp $(INCLUDE_DIR)/*
	mkdir -p $(BIN_DIR)
	
	$(G++) $(SRC_DIR)/index_ui.cpp $(SRC_DIR)/index.cpp -o $(BIN_DIR)/index_ui

bin/sparse_ui: $(SRC_DIR)/sparse_ui.cpp $(SRC_DIR)/index.cpp $(INCLUDE_DIR)/*
	mkdir -p $(BIN_DIR)
	
	$(G++) $(SRC_DIR)/sparse_ui.cpp -o $(BIN_DIR)/sparse_ui


clean:
	rm -rf bin/index_ui bin/sparse_ui