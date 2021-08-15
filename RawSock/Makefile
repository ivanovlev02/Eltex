.PHONY := clean
SOURCE1 := client.c
SOURCE2 := server.c
BIN1 := client
BIN2 := server

server: $(BIN1)
	gcc $(SOURCE2) -o $(BIN2)

client:
	gcc $(SOURCE1) -o $(BIN1)

clean:
	rm -rf $(BIN1) $(BIN2)
