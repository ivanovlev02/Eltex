bin := bitwise
source := bitwise_oper.c

.PHONY := clean

all: $(bin) clean

$(bin): $(source)
	gcc $(source) -o $(bin)

clean:
	rm -rf $(bin)
