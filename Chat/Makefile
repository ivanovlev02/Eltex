.PHONY := clean

server: client
	gcc server.c -o server -g -lpthread

client:
	gcc client.c -o client -g -lpthread

clean:
	rm -rf client server
