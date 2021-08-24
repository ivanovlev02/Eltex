C := gcc
FLAG := -g
BIN := test
SOURCE := test.c
#HEADER :=

.PHONY := clean

server: client
			$(CC) server.c -o server $(FLAG)

client:
		$(CC) client.c -o client $(FLAG)

clean:
			rm -rf client server
