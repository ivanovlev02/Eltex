.PHONY := clean lib

BIN: main.c libfunc_calc.so
	gcc main.c -ldl -o BIN -Wl,-rpath,.

main.o: main.c
	gcc -c main.c

#libfunc_calc.so: func_add.c func_div.c func_mul.c func_sub.c
#	gcc -fPIC -shared func_add.c func_div.c func_mul.c func_sub.c -o libfunc_calc.so

clean:
	rm -rf *.o *.a BIN

lib:
	gcc -fPIC -shared func_add.c func_div.c func_mul.c func_sub.c -o libfunc_calc.so
