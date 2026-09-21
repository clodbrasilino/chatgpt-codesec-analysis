#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void decimalToBinary(int n) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[sizeof(int) * CHAR_BIT + 1];
    int index = 0;

    if (n == 0) {
        printf("0");
        return;
    }

    while (n > 0 && index < (int)(sizeof(binary) - 1)) {
        binary[index] = (n % 2) + '0';
        n = n / 2;
        index++;
    }
    binary[index] = '\0';

    for (int i = index - 1; i >= 0; i--) {
        printf("%c", binary[i]);
    }
}

int main(void) {
    int num;

    printf("Enter a decimal number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (num < 0) {
        fprintf(stderr, "Please enter a non-negative integer\n");
        return 1;
    }

    printf("Binary equivalent: ");
    decimalToBinary(num);
    printf("\n");

    return 0;
}