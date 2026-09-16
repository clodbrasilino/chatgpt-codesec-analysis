#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int leftRotate(unsigned int n, unsigned int d) {
    unsigned int bitsInInteger = sizeof(unsigned int) * CHAR_BIT;
    
    if (d >= bitsInInteger) {
        d = d % bitsInInteger;
    }
    
    if (d == 0) {
        return n;
    }
    
    return (n << d) | (n >> (bitsInInteger - d));
}

int main(void) {
    unsigned int number = 0;
    unsigned int rotation = 0;
    
    if (scanf("%u %u", &number, &rotation) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned int result = leftRotate(number, rotation);
    printf("%u\n", result);
    
    return EXIT_SUCCESS;
}