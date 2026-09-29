#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimal_to_binary(int n, char *binary, size_t binary_size, int *length) {
    size_t index = 0;
    
    if (n == 0) {
        if (binary_size > 1) {
            binary[index++] = '0';
        }
    } else {
        while (n > 0 && index < binary_size - 1) {
            binary[index++] = (n % 2) + '0';
            n = n / 2;
        }
    }
    
    if (binary_size > 0) {
        binary[index] = '\0';
    }
    *length = (int)index;
    
    size_t start = 0;
    size_t end = index > 0 ? index - 1 : 0;
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
    
    memset(binary, 0, sizeof(binary));
    decimal_to_binary(decimal, binary, sizeof(binary), &length);
    
    printf("Binary equivalent: %s\n", binary);
    
    return EXIT_SUCCESS;
}