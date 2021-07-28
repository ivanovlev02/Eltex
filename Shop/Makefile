bin := shop
source := shop.c
flag := -lpthread

.PHONY := clean

$(bin): $(source)
	gcc $(source) -o $(bin) $(flag)

clean:
	rm -rf $(bin)
