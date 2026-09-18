#include<stdio.h>

unsigned int setEvenBits(unsigned int num){
    unsigned int mask = 0xAAAAAAAA;
    return num | mask;
}

int main(){
    unsigned int num = 5;
    unsigned int result = setEvenBits(num);
    printf("Result after setting even bits: %u", result);
    return 0;
}