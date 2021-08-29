#include <stdio.h>
#include "func_calc.h"

int menu();

int main(void){
    
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
                printf("\n%d + %d = %d\n", a, b, addition(a, b));
                break;
            case 2:
                printf("Число A: ");
                scanf("%d", &a);
                printf("Число B: ");
                scanf("%d", &b);
                printf("\n%d - %d = %d\n", a, b, subtraction(a, b));
                break;
            case 3:
                printf("Число A: ");
                scanf("%d", &a);
                printf("Число B: ");
                scanf("%d", &b);
                printf("\n%d * %d = %d\n", a, b, multiplication(a, b));
                break;
            case 4:
                printf("Число A: ");
                scanf("%d", &a);
                printf("Число B: ");
                scanf("%d", &b);
                printf("\n%d / %d = %.2f\n", a, b, division((float)a, (float)b));
                break;
            case 5:
                printf("До свидания!\n");
                break;
        }
    }while(count != 5);

    return 0;
}
int menu(){
    int count;
    printf("\nВыберите действие\n1.Сложение\n2.Вычитание\n3.Умножение\n4.Деление\n5.Выход\n");
    scanf("%d", &count);
    return count;
}
