#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
//#include "func_calc.h"

int menu();

int main(int argc, char* argv[]){
    
    void* LIB_so;
    char* ERROR;
    int (*add)(int, int);
    int (*sub)(int, int);
    int (*mul)(int, int);
    float (*div)(float, float);

    //LIB_so = dlopen("/mnt/usbstorage/My_tests/DLfcn/libfunc_calc.so", 
    //        RTLD_LAZY);

    //        gcc main.c -ldl -o BIN -Wl,-rpath,.
    LIB_so = dlopen("libfunc_calc.so", RTLD_LAZY);

    if(ERROR = dlerror()){
        printf("dlopen() error: %s\n", ERROR);
        exit(1);
    }

    add = dlsym(LIB_so, "addition");
    if(ERROR = dlerror()){
        printf("dlsym() function addition error: %s\n", ERROR);
        exit(1);
    }

    sub = dlsym(LIB_so, "subtraction");
    if(ERROR = dlerror()){
        printf("dlsym() function subtraction error: %s\n", ERROR);
        exit(1);
    }

    mul = dlsym(LIB_so, "multiplication");
    if(ERROR = dlerror()){
        printf("dlsym() function multiplication error: %s\n", ERROR);
        exit(1);
    }

    div = dlsym(LIB_so, "division");
    if(ERROR = dlerror()){
        printf("dlsym() function division error: %s\n", ERROR);
        exit(1);
    }

    int count;
    int a, b;

    do{
        count = menu();
        switch(count){
            case 1:
                printf("Число A: ");
                scanf("%d", &a);
                printf("Число B: ");
                scanf("%d", &b);
                printf("\n%d + %d = %d\n", a, b, add(a, b));
                break;
            case 2:
                printf("Число A: ");
                scanf("%d", &a);
                printf("Число B: ");
                scanf("%d", &b);
                printf("\n%d - %d = %d\n", a, b, sub(a, b));
                break;
            case 3:
                printf("Число A: ");
                scanf("%d", &a);
                printf("Число B: ");
                scanf("%d", &b);
                printf("\n%d * %d = %d\n", a, b, mul(a, b));
                break;
            case 4:
                printf("Число A: ");
                scanf("%d", &a);
                printf("Число B: ");
                scanf("%d", &b);
                printf("\n%d / %d = %.2f\n", a, b, div((float)a, (float)b));
                break;
            case 5:
                printf("До свидания!\n");
                break;
        }
    }while(count != 5);

    dlclose(LIB_so);
    //return 0;
}
int menu(){
    int count;
    printf("\nВыберите действие\n1.Сложение\n2.Вычитание\n3.Умножение\n4.Деление\n5.Выход\n");
    scanf("%d", &count);
    return count;
}
