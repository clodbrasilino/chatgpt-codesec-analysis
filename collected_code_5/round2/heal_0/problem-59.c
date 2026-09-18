#include <stdio.h>
#include <stdlib.h>

long long findNthOctagonalNumber(int n){
    if (n <= 0){
        printf("Invalid Input");
        return -1;
    }

    return n * (3 * n - 2);
}

int main(void){
    int n;
    printf("Enter number: ");
    scanf("%d", &n);

    long long octagonalNumber = findNthOctagonalNumber(n);
    if (octagonalNumber != -1){
        printf("The %dth octagonal number is %lld\n", n, octagonalNumber);
    }

    return 0;
}