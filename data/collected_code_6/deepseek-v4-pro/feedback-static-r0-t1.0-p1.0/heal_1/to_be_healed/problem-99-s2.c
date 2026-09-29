#include <stdio.h>
#include <stdlib.h>

void decimal_to_binary(int n, char *binary, int *length) {
    int index = 0;
    
    if (n == 0) {
        binary[index++] = '0';
    } else {
        while (n > 0) {
            binary[index++] = (n % 2) + '0';
            n = n / 2;
        }
    }
    
    binary[index] = '\0';
    *length = index;
    
    int start = 0;
    int end = index - 1;
    while (start < end) {
        char temp = binary[start];
        binary[start] = binary[end];
        binary[end] = temp;
        start++;
        end--;
    }
}

int main(void) {
    int decimal;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary[33];
    int length = 0;
    
    printf("Enter a decimal number: ");
    if (scanf("%d", &decimal) != 1) {
        printf("Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (decimal < 0) {
        printf("Please enter a non-negative integer\n");
        return EXIT_FAILURE;
    }
    
    decimal_to_binary(decimal, binary, &length);
    
    printf("Binary equivalent: %s\n", binary);
    
    return EXIT_SUCCESS;
}