bin := texteditor
source := texteditor.c
compiler := gcc

.PHONY := clean

$(bin): $(source)
		$(compiler) $(source) -o $(bin) -lncurses -lpanel

clean:
	rm -rf $(bin)
