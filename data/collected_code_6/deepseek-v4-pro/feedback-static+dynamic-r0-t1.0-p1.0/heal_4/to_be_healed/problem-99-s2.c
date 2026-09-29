#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimal_to_binary(int n, char *binary, size_t size, int *length) {
    size_t index = 0;
    
    if (size == 0) {
        *length = 0;
        return;
    }
    
    if (n == 0) {
        binary[index++] = '0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char temp[33];
        size_t temp_index = 0;
        size_t temp_size = sizeof(temp);
        
        while (n > 0 && temp_index < temp_size) {
            temp[temp_index++] = (n % 2) + '0';
            n = n / 2;
        }
        
        for (size_t i = 0; i < temp_index && index < size - 1; i++) {
            binary[index++] = temp[temp_index - 1 - i];
        }
    }
    
    if (index < size) {
        binary[index] = '\0';
    } else {
        binary[size - 1] = '\0';
        index = size - 1;
    }
    
    *length = (int)index;
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
    
    decimal_to_binary(decimal, binary, sizeof(binary), &length);
    
    printf("Binary equivalent: %s\n", binary);
    
    return EXIT_SUCCESS;
}