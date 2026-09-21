#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char octal_buffer[BUFFER_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[64];
    char *endptr;
    unsigned long temp_value;
    
    printf("Enter a decimal number: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    temp_value = strtoul(input_buffer, &endptr, 10);
    
    if (errno != 0 || endptr == input_buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (temp_value > UINT_MAX) {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }
    
    decimal = (unsigned int)temp_value;
    
    if (decimal_to_octal(decimal, octal_buffer, sizeof(octal_buffer)) != 0) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Octal: %s\n", octal_buffer);
    
    return EXIT_SUCCESS;
}