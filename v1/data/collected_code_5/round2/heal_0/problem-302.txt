#include <stdio.h>

unsigned int msbNum(unsigned int num){
    if(num==0) return 0;
    int msb = 0;
    while(num){
        num>>=1;
        msb++;
    }
    return msb-1;
}

int main(){
    unsigned int num;
    printf("Enter a number: ");
    scanf("%u", &num);
    unsigned int result = msbNum(num);
    printf("Most significant set bit number is: %u\n", result);
    return 0;
}