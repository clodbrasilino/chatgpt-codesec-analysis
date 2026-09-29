#include <stdio.h>
#include <stdlib.h>

int * decimalToBinary(int num) {
    int *binary = malloc(sizeof(int) * 32); 
    int index = 0; 

    while (num > 0) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'binary' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        binary[index++] = num % 2;
        num = num / 2;
    }
    
    return binary;
}

int main() {
    int number, i;
    printf("Enter any number: ");
    scanf("%d", &number);
    int *binary = decimalToBinary(number);
    for(i = 31; i >= 0; i--) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*binary_12 + _3' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        printf("%d", binary[i]);
    }
    printf("\n");
    free(binary);
    return 0;
}