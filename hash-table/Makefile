CC = gcc
CFLAGS = -Wall -Wextra -std=c2x -pedantic 
LDFLAGS = -lm

ifeq ($(DEBUG), 1)
	CFLAGS += -g
else
	CFLAGS += -DNDEBUG 
endif

SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(SRC_DIR)/*.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(LDFLAGS)

clean:
	-rm $(BIN_DIR)/*

.PHONY: all clean