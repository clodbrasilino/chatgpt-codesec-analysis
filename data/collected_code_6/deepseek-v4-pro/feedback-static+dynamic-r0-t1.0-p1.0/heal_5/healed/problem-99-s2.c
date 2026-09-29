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
        char temp[32];
        size_t temp_index = 0;
        size_t temp_size = sizeof(temp);
        
        while (n > 0 && temp_index < temp_size - 1) {
            temp[temp_index++] = (n % 2) + '0';
            n = n / 2;
        }
        temp[temp_index] = '\0';
        
        while (temp_index > 0 && index < size - 1) {
            binary[index++] = temp[--temp_index];
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