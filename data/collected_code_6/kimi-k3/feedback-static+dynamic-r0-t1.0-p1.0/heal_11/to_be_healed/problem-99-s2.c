#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#define BINARY_BUFFER_SIZE (sizeof(unsigned int) * CHAR_BIT + 1)
#define INPUT_BUFFER_SIZE 32

int decimal_to_binary(unsigned int decimal, char *buffer, size_t buffer_size) {
    size_t index;
    size_t i;
    size_t required_size;
    unsigned int temp;
    
    if (buffer == NULL) {
        return -1;
    }
    
    required_size = 1;
    temp = decimal;
    if (temp == 0) {
        required_size = 2;
    } else {
        while (temp > 0) {
            required_size++;
            temp /= 2;
        }
    }
    
    if (buffer_size < required_size) {
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
    
    if (index >= buffer_size) {
        return -1;
    }
    
    buffer[index] = '\0';
    
    for (i = 0; i < index / 2; i++) {
        char temp_char = buffer[i];
        buffer[i] = buffer[index - 1 - i];
        buffer[index - 1 - i] = temp_char;
    }
    
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary_buffer[BINARY_BUFFER_SIZE];
    unsigned int decimal_number;
    int result;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[INPUT_BUFFER_SIZE];
    char *endptr;
    unsigned long value;
    size_t input_len;
    size_t i;
    int valid;
    
    printf("Enter a decimal number: ");
    
    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    input_len = 0;
    valid = 0;
    for (i = 0; i < sizeof(input_buffer); i++) {
        if (input_buffer[i] == '\0') {
            input_len = i;
            valid = 1;
            break;
        }
    }
    
    if (!valid) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (input_len > 0 && input_buffer[input_len - 1] == '\n') {
        input_buffer[input_len - 1] = '\0';
        input_len--;
    }
    
    if (input_len == 0) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    value = strtoul(input_buffer, &endptr, 10);
    
    if (errno != 0 || endptr == input_buffer || *endptr != '\0' || value > UINT_MAX) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    decimal_number = (unsigned int)value;
    
    memset(binary_buffer, 0, sizeof(binary_buffer));
    
    result = decimal_to_binary(decimal_number, binary_buffer, sizeof(binary_buffer));
    
    if (result != 0) {
        fprintf(stderr, "Error: Conversion failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Binary equivalent: %s\n", binary_buffer);
    
    return EXIT_SUCCESS;
}