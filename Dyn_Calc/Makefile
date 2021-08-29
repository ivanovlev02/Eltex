BIN: main.o libfunc_calc.so
	gcc -o BIN main.o -L. -lfunc_calc

main.o: main.c
	gcc -c main.c

libfunc_calc.so: func_add.o func_div.o func_mul.o func_sub.o
	gcc -shared -o libfunc_calc.so func_add.o func_div.o func_mul.o func_sub.o

func_add.o: func_add.c
	gcc -fPIC -c func_add.c

func_div.o: func_div.c
	gcc -fPIC -c func_div.c

func_mul.o: func_mul.c
	gcc -fPIC -c func_mul.c

func_sub.o: func_sub.c
	gcc -fPIC -c func_sub.c

clean:
	rm -rf *.o *.a BIN
