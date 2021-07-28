#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SHOPS 5
#define BUYERS 3
#define NEED_MIN 9700
#define NEED_MAX 10300
#define SHIPPING 200
#define PRODUCT_MAX 1100
#define PRODUCT_MIN 900

pthread_mutex_t mutex[SHOPS];
int shops[SHOPS];
int wait = 1;

void* buyer(void* ptr){
    int* need = (int*)ptr;
    int i, tmp;
    srand(pthread_self());
    while(*need > 0){
        i = rand() % 5;
        pthread_mutex_lock(&mutex[i]);
            tmp = shops[i];
            shops[i] = 0;
        pthread_mutex_unlock(&mutex[i]);
        *need -= tmp;
        printf("Buyer: %x, shop: %d, %d need: %d\n", (int)pthread_self(), i, tmp, *need);
        sleep(1);
    }
    printf("EXIT\n");
    return NULL;
}

void* linker(){
    int i, cycle = 1;
    srand(pthread_self());
    while(cycle){
        if(!wait){
            cycle = 0;
            break;
        }
        i = rand() % 5;
        pthread_mutex_lock(&mutex[i]);
            shops[i] += 200;
            printf("Linker: %d %d\n", i, shops[i]);
        pthread_mutex_unlock(&mutex[i]);
        sleep(2);
    }
        return NULL;
}

int main(int argc, char** argv){
    //srand(time(NULL));
    pthread_t buyers[BUYERS];
    pthread_t link;
    int need[BUYERS];
    int i;
    
    for(i = 0; i < SHOPS; i++){
        pthread_mutex_init(&mutex[i], NULL);
        shops[i] = rand() % (PRODUCT_MAX - PRODUCT_MIN) + PRODUCT_MIN;
        printf("Shop: %d, product: %d\n", i + 1, shops[i]);
        /*if(pthread_mutex_init(&mutex[i], NULL)){
            perror("mutex");
            exit(EXIT_FAILURE);
        }*/
    }

    /*for(int i = 0; i < SHOPS; i++){
        shops[i] = rand() % (PRODUCT_MAX - PRODUCT_MIN) + PRODUCT_MIN;
        printf("Shop: %d, product: %d\n", i + 1, shops[i]);
    }*/

   
    for(i = 0; i < BUYERS; i++){
        need[i] = rand() % (NEED_MAX - NEED_MIN) + NEED_MIN;
        printf("Buyer: %d, need: %d\n", i + 1, need[i]);
        if(pthread_create(&buyers[i], NULL, buyer, &need[i]) != 0){
            perror("thread create");
            exit(EXIT_FAILURE);
        }
    }
    if(pthread_create(&buyers[i], NULL, linker, NULL) != 0){
        perror("linker create");
        exit(EXIT_FAILURE);
    }
    //wait = 0;
    for(i = 0; i < BUYERS; i++){
        pthread_join(buyers[i], NULL);
        if(pthread_join(buyers[i], NULL) != 0){
            perror("pthread join");
            exit(EXIT_FAILURE);
        }
    }
    wait = 0;
    pthread_join(link, NULL);
    printf("SHOP: ");
    for(i = 0; i < BUYERS; i++){
        printf("%d ", shops[i]);
        pthread_mutex_destroy(&mutex[i]);
    }

    exit(EXIT_SUCCESS);
}
