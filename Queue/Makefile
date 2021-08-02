.PHONY := clean

server: client
	gcc server.c -o server -lpthread

client:
	gcc client.c -o client -lpthread

clean:
	rm -rf client server
