#include <stdio.h>
#include <stdlib.h>

#define SIZE_MAX (~(size_t)0)

long long getNthOctagonalNumber(unsigned int n){
    if(n == 0 || n > ((SIZE_MAX - 1) / 3))
        return -1;

    return n * (3 * n - 2);
}

int main(void){
    unsigned int nth;
    long long result;

    printf("Enter Nth Octagonal Number: ");
    scanf("%u", &nth);

    result = getNthOctagonalNumber(nth);

    if(result == -1)
        printf("Invalid Input or Calculation Overflow\n");
    else
        printf("%lld\n", result);

    return 0;
}