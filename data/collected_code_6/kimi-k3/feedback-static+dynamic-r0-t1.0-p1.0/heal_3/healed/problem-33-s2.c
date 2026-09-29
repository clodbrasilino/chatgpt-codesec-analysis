#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define BITS_PER_BYTE 8
#define MAX_BINARY_LENGTH (sizeof(unsigned long long) * BITS_PER_BYTE + 1)
#define MAX_INPUT_LENGTH 64

void decimal_to_binary(unsigned long long decimal, char *binary_buffer, size_t buffer_size) {
    if (binary_buffer == NULL || buffer_size == 0) {
        return;
    }

    if (buffer_size < MAX_BINARY_LENGTH) {
        binary_buffer[0] = '\0';
        return;
    }

    if (decimal == 0) {
        binary_buffer[0] = '0';
        binary_buffer[1] = '\0';
        return;
    }

    size_t index = 0;
    unsigned long long temp = decimal;

    while (temp > 0 && index < buffer_size - 1) {
        binary_buffer[index++] = (char)((temp % 2) + '0');
        temp /= 2;
    }

    binary_buffer[index] = '\0';

    size_t left = 0;
    size_t right = index - 1;
    while (left < right) {
        char swap = binary_buffer[left];
        binary_buffer[left] = binary_buffer[right];
        binary_buffer[right] = swap;
        left++;
        right--;
    }
}

int main(void) {
    char *input_buffer = NULL;
    char *binary_buffer = NULL;
    unsigned long long decimal_number;
    char *end_ptr;
    size_t input_size = MAX_INPUT_LENGTH;

    input_buffer = (char *)malloc(input_size);
    if (input_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    binary_buffer = (char *)malloc(MAX_BINARY_LENGTH);
    if (binary_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(input_buffer);
        return EXIT_FAILURE;
    }

    printf("Enter a decimal number: ");

    if (fgets(input_buffer, input_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }

    size_t len = strnlen(input_buffer, input_size);
    if (len == input_size) {
        fprintf(stderr, "Input too long\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }

    if (len > 0 && input_buffer[len - 1] == '\n') {
        input_buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0 || input_buffer[0] == '\0') {
        fprintf(stderr, "Empty input\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }

    errno = 0;
    decimal_number = strtoull(input_buffer, &end_ptr, 10);

    if (errno == ERANGE) {
        fprintf(stderr, "Number out of range\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }

    if (end_ptr == input_buffer) {
        fprintf(stderr, "No valid digits found\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }

    if (*end_ptr != '\0') {
        fprintf(stderr, "Invalid characters in input\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }

    decimal_to_binary(decimal_number, binary_buffer, MAX_BINARY_LENGTH);

    if (binary_buffer[0] == '\0') {
        fprintf(stderr, "Conversion failed\n");
        free(input_buffer);
        free(binary_buffer);
        return EXIT_FAILURE;
    }

    printf("Binary representation: %s\n", binary_buffer);

    free(input_buffer);
    free(binary_buffer);

    return EXIT_SUCCESS;
}