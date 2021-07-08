bin := array
sources := array.c
headers :=

.PHONY := clean

all: $(bin) clean

$(bin): $(sources)
		gcc $(sources) -o $(bin)

$(bin): $(headres)

clean:
		rm -rf $(bin)
