#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int decimal_to_octal(unsigned int decimal, char *buffer, size_t buffer_size) {
    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }
    
    size_t required = 1;
    unsigned int temp = decimal;
    
    if (temp == 0) {
        required = 2;
    } else {
        while (temp > 0) {
            required++;
            temp /= 8;
        }
    }
    
    if (buffer_size < required) {
        return -1;
    }
    
    size_t index = 0;
    
    if (decimal == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }
    
    temp = decimal;
    while (temp > 0) {
        buffer[index++] = (char)((temp % 8) + '0');
        temp /= 8;
    }
    
    for (size_t i = 0; i < index / 2; i++) {
        char swap = buffer[i];
        buffer[i] = buffer[index - 1 - i];
        buffer[index - 1 - i] = swap;
    }
    
    buffer[index] = '\0';
    
    return 0;
}

int main(void) {
    unsigned int decimal;
    char octal_buffer[12];
    
    printf("Enter a decimal number: ");
    
    if (scanf("%u", &decimal) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (decimal_to_octal(decimal, octal_buffer, sizeof(octal_buffer)) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Octal: %s\n", octal_buffer);
    
    return EXIT_SUCCESS;
}