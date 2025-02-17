CC = gcc
CFLAGS = -Wall -Wextra -std=c2x -pedantic -fno-builtin

SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(SRC_DIR)/*.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@

run: clean all
	./$(BIN_DIR)/main

clean:
	-rm $(BIN_DIR)/*

.PHONY: all clean