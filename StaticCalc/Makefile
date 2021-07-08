BIN: main.o libfunc_calc.a
	gcc -o BIN main.o -L. -lfunc_calc

main.o: main.c
	gcc -c main.c

libfunc_calc.a: func_add.o func_div.o func_mul.o func_sub.o
	ar rc libfunc_calc.a func_add.o func_div.o func_mul.o func_sub.o

func_add.o: func_add.c
	gcc -c func_add.c

func_div.o: func_div.c
	gcc -c func_div.c

func_mul.o: func_mul.c
	gcc -c func_mul.c

func_sub.o: func_sub.c
	gcc -c func_sub.c

clean:
	rm -rf *.o *.a BIN
