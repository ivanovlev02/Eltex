bin := main
source := main.c
compiler := gcc

.PHONY := clean

$(bin): $(source)
		$(compiler) $(source) -o $(bin) -lncurses -lpanel

clean:
	rm -rf $(bin)
