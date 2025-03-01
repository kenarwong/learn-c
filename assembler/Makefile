CC = gcc
CFLAGS = -Wall -Wextra -std=c2x -pedantic -fno-builtin

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
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@

run-as: clean all
	./$(BIN_DIR)/main -a ins.s out.o

debug-as: clean all 
	gdb \
		-ex 'file ./$(BIN_DIR)/main' \
		-ex 'break main' \
		-ex continue \
		-ex 'run -a ins.s out.o' 

run-d: clean all
	./$(BIN_DIR)/main -d ins.o out.s

debug-d: clean all 
	gdb \
		-ex 'file ./$(BIN_DIR)/main' \
		-ex 'break main' \
		-ex continue \
		-ex 'run -d ins.o out.s' 

clean:
	-rm $(BIN_DIR)/*

.PHONY: all clean