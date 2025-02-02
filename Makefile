CC = gcc
CFLAGS = -Wall -Wextra -o0
TESTFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lcriterion

OBJ_DIR = obj
BIN_DIR = bin


$(OBJ_DIR)/adcs.o: adcs.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ adcs.c

test: $(OBJ_DIR)/adcs.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/test tests/test.c $< $(TESTFLAGS)
	./$(BIN_DIR)/test --verbose > ./tests/test_$(shell date +%Y-%m-%d-%H-%M-%S).txt 2>&1

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
