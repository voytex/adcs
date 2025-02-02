# Makefile for ARCSEC project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -o0
TESTFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lcriterion

# Source and object files
OBJ_DIR = obj
BIN_DIR = bin


$(OBJ_DIR)/adcs.o: adcs.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ adcs.c

test: $(OBJ_DIR)/adcs.o
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test $< tests/test.c $(TESTFLAGS)
	$(BIN_DIR)/test


# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
