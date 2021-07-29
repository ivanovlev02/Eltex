CC := gcc
FLAG := -o
BIN := cmd
SOURCE := cmd.c

.PHONY := clean

$(BIN): $(SOURCE)
		$(CC) $(SOURCE) $(FLAG) $(BIN)

clean:
	rm -rf $(BIN)
