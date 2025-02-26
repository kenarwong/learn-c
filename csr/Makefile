CC = gcc
CFLAGS = -Wall -Wextra -std=c2x -pedantic

SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
TARGETS = $(patsubst $(SRC_DIR)/%.c,%,$(SRC_FILES))

BIN_DIR = bin

all: $(addprefix $(BIN_DIR)/, $(TARGETS))

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean