CC = gcc
CFLAGS = -Wall -Wextra 

ifeq ($(PEDANTIC), 1)
	CFLAGS += -pedantic
endif

SRC = closure.c
TARGET = closure

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

assembly: $(SRC)
	$(CC) $(CFLAGS) -S $(SRC)

clean:
	-rm -f $(TARGET)

.PHONY: all clean