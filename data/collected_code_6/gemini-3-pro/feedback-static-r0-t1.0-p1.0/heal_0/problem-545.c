#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned int toggleFirstAndLastBits(unsigned int n) {
    if (n == 0) {
        return (1U << (sizeof(unsigned int) * CHAR_BIT - 1)) | 1U;
    }
    
    unsigned int mask = 1U;
    mask |= (1U << (sizeof(unsigned int) * CHAR_BIT - 1));
    
    return n ^ mask;
}

int main(void) {
    unsigned int number = 0;
    unsigned int result = 0;

    printf("Enter a positive integer: ");
    if (scanf("%u", &number) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = toggleFirstAndLastBits(number);
    printf("Result: %u\n", result);

    return EXIT_SUCCESS;
}