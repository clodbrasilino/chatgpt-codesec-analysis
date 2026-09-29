#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void decimalToBinary(int n) {
    if (n < 0) {
        printf("Error: Please enter a non-negative integer.\n");
        return;
    }

    if (n == 0) {
        printf("0\n");
        return;
    }

    unsigned int num = (unsigned int)n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binaryString[sizeof(num) * CHAR_BIT + 1];
    int index = 0;

    while (num > 0 && index < (int)(sizeof(binaryString) - 1)) {
        binaryString[index++] = (num % 2) ? '1' : '0';
        num /= 2;
    }

    for (int i = index - 1; i >= 0; i--) {
        putchar(binaryString[i]);
    }
    putchar('\n');
}

int main(void) {
    int number = 0;
    
    if (scanf("%d", &number) != 1) {
        printf("Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    decimalToBinary(number);
    
    return EXIT_SUCCESS;
}