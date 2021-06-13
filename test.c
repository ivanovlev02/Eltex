#include <stdio.h>

int main(){   
    int a = 0x00DDAABB;
    int c;
    
    for(int i=8; i<=24;i+=8){
        c = (a >> i) & 0xFF;
        printf("%X\n", c);
    }
    a = a | 0x00BB0000;
    printf("%X\n", a);
}
