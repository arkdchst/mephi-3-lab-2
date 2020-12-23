.PHONY: all clean
.DEFAULT_GOAL := all

INCLUDE_DIR := include
SRC_DIR := src
BIN_DIR := bin

G++ := g++ -g -std=c++17 -I$(INCLUDE_DIR)

all: bin/index_ui bin/sparse_ui bin/index_test bin/sparse_test

bin/index_ui: $(SRC_DIR)/index_ui.cpp $(SRC_DIR)/index.cpp $(INCLUDE_DIR)/*
	mkdir -p $(BIN_DIR)
	
	$(G++) $(SRC_DIR)/index_ui.cpp $(SRC_DIR)/index.cpp -o $(BIN_DIR)/index_ui

bin/sparse_ui: $(SRC_DIR)/sparse_ui.cpp $(SRC_DIR)/index.cpp $(INCLUDE_DIR)/*
	mkdir -p $(BIN_DIR)
	
	$(G++) $(SRC_DIR)/sparse_ui.cpp -o $(BIN_DIR)/sparse_ui

bin/index_test: $(SRC_DIR)/index_test.cpp $(SRC_DIR)/index.cpp $(INCLUDE_DIR)/*
	mkdir -p $(BIN_DIR)
	
	$(G++) -lgtest -lgtest_main $(SRC_DIR)/index_test.cpp $(SRC_DIR)/index.cpp -o $(BIN_DIR)/index_test

bin/sparse_test: $(SRC_DIR)/sparse_test.cpp $(SRC_DIR)/index.cpp $(INCLUDE_DIR)/*
	mkdir -p $(BIN_DIR)
	
	$(G++) -lgtest -lgtest_main $(SRC_DIR)/sparse_test.cpp -o $(BIN_DIR)/sparse_test


clean:
	rm -rf bin/index_ui bin/sparse_ui bin/index_test bin/sparse_test