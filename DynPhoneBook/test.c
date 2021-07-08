#include <stdio.h>
#include <malloc.h>

struct phone_book{
    char first_name[30];
    char last_name[30];
    char number[12];
};

int menu();
void add_phone_book(int);

int main(void){
    struct phone_book* pb;
    char delete_or_search[20];
    int count;
    int size = 1;
    int n = -1;
    pb = (struct phone_book*)malloc(size * sizeof(struct phone_book));
    
    do{
        count = menu();
        getchar();
        switch(count){
            case 1:
                /*Добавление*/
                n++;
                if(size >= 1){
                    size++;
                    pb = (struct phone_book*)realloc(pb, size * sizeof(struct phone_book));
                }

                printf("\nИмя: ");
                gets(pb[n].first_name);
                printf("Фамилия: ");
                gets(pb[n].last_name);
                printf("Телефон: ");
                gets(pb[n].number);
                break;
            case 2:
                /*Удаление*/
                printf("\nВведите Имя, Фамилию или телефон: ");
                gets(delete_or_search);
                for(int i = 0; i <= n; i++){
                    if((strcmp(delete_or_search, pb[i].first_name) == 0) ||
                       (strcmp(delete_or_search, pb[i].last_name) == 0) ||
                       (strcmp(delete_or_search, pb[i].number) == 0)){
                        pb[i].first_name[0] = '\0';
                        pb[i].last_name[0] = '\0';
                        pb[i].number[0] = '\0';
                        printf("\nКонтакт удален\n");
                    }
                }
                break;
            case 3:
                /*Поиск*/
                printf("\nВведите Имя, Фамилию или телефон: ");
                gets(delete_or_search);
                for(int i = 0; i <= n; i++){
                    if((strcmp(delete_or_search, pb[i].first_name) == 0) ||
                       (strcmp(delete_or_search, pb[i].last_name) == 0) ||
                       (strcmp(delete_or_search, pb[i].number) == 0)){
                        printf("\nИмя: %s", pb[i].first_name);
                        printf("\nФамилия: %s", pb[i].last_name);
                        printf("\nТелефон: %s\n", pb[i].number);
                    } else {
                        printf("\nКонтакт не найден\n");
                    }
                }
                break;
            case 4:
                /*Просмотр*/
                if(n == -1){
                    printf("\nТелефонная книга пуста!\n");
                } else {
                    printf("\nВписанные контакты\n");
                    for(int i = 0; i <= n; i++){
                        if(pb[i].first_name[0]){
                            printf("\nИмя: %s", pb[i].first_name);
                            printf("\nФамилия: %s", pb[i].last_name);
                            printf("\nТелефон: %s\n", pb[i].number);
                    
                        }
                    }
                }
                break;
            default:
                printf("\nВсего хорошего!\n");
                break;
        }
    }while(count != 5);

    free(pb);
    return 0;
}

int menu(){
    int count;
    printf("\nТелефонная книга:\n1. Добавить\n2. Удалить\n3. Найти\n4. Смотреть\n5. Выход\n");
    scanf("%d", &count);
    return count;
}
