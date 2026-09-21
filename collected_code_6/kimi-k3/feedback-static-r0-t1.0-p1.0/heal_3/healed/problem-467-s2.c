#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define BUFFER_SIZE 12

int decimal_to_octal(unsigned int decimal, char *buffer, size_t buffer_size) {
    if (buffer == NULL || buffer_size < 2) {
        return -1;
    }
    
    if (decimal == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 0;
    }
    
    unsigned int temp = decimal;
    size_t required = 0;
    while (temp > 0) {
        required++;
        temp /= 8;
    }
    
    if (required + 1 > buffer_size) {
        return -1;
    }
    
    size_t i;
    for (i = 0; i < required; i++) {
        buffer[required - 1 - i] = (char)((decimal % 8) + '0');
        decimal /= 8;
    }
    buffer[required] = '\0';
    
    return 0;
}

int main(void) {
    unsigned int decimal;
    char octal_buffer[BUFFER_SIZE];
    
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