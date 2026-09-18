#include <stdio.h>

#define SIZE 32

void decimalToBinary(int n, char binaryNumber[SIZE]){
    int i;
    for(i = 0; i<SIZE; i++){
        binaryNumber[i] = (n >> (SIZE-1 - i)) & 1 ? '1' : '0';
    }
}

int main(){
    int n;
    char binaryNumber[SIZE + 1];
    binaryNumber[SIZE] = '\0';

    printf("Enter a decimal number: ");
    scanf("%d", &n);

    decimalToBinary(n, binaryNumber);
    printf("Binary of %d is %s\n", n, binaryNumber);

    return 0;
}