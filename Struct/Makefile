BIN := phone_book
SOURCE := phone_book.c
CC := gcc
CFLAG := -o

all: $(BIN) clean

$(BIN): $(SOURCE)
		$(CC) $(SOURCE) $(CFLAG) $(BIN)

clean:
	rm -rf $(BIN)
