#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define BINARY_BUFFER_SIZE (sizeof(unsigned int) * CHAR_BIT + 1)

int decimal_to_binary(unsigned int decimal, char *buffer, size_t buffer_size) {
    size_t index;
    size_t i;
    size_t start;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    unsigned int temp;
    
    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }
    
    if (buffer_size < BINARY_BUFFER_SIZE) {
        return -1;
    }
    
    index = 0;
    
    if (decimal == 0) {
        buffer[index++] = '0';
    } else {
        temp = decimal;
        while (temp > 0 && index < buffer_size - 1) {
            buffer[index++] = (char)((temp % 2) + '0');
            temp = temp / 2;
        }
    }
    
    buffer[index] = '\0';
    
    start = 0;
    for (i = 0; i < index / 2; i++) {
        char temp_char = buffer[start + i];
        buffer[start + i] = buffer[index - 1 - i];
        buffer[index - 1 - i] = temp_char;
    }
    
    return 0;
}

int main(void) {
    char binary_buffer[BINARY_BUFFER_SIZE];
    unsigned int decimal_number;
    int result;
    
    printf("Enter a decimal number: ");
    
    if (scanf("%u", &decimal_number) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = decimal_to_binary(decimal_number, binary_buffer, sizeof(binary_buffer));
    
    if (result != 0) {
        fprintf(stderr, "Error: Conversion failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Binary equivalent: %s\n", binary_buffer);
    
    return EXIT_SUCCESS;
}