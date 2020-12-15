.PHONY: all clean
.DEFAULT_GOAL := all

INCLUDE_PATH := include

G++ := g++ -std=c++17 -Wall -I$(INCLUDE_PATH)

all: test tests

test: $(INCLUDE_PATH)/* src/*
	$(G++) src/test.cpp -o test

tests: $(INCLUDE_PATH)/* src/*
	$(G++) src/tests.cpp -o tests

clean:
	rm -rf test tests