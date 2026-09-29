#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 256

long ascii_sum(const char *str, size_t max_len)
{
    long sum = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, max_len);
    for (i = 0; i < len; i++) {
        sum += (long)(unsigned char)str[i];
    }

    return sum;
}

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read_len;
    long result;

    printf("Enter a string: ");

    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len < 0) {
        free(buffer);
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    if (read_len > 0 && buffer[read_len - 1] == '\n') {
        buffer[read_len - 1] = '\0';
        read_len--;
    }

    if ((size_t)read_len >= MAX_INPUT_SIZE) {
        buffer[MAX_INPUT_SIZE - 1] = '\0';
    }

    result = ascii_sum(buffer, MAX_INPUT_SIZE);
    if (result < 0) {
        free(buffer);
        fprintf(stderr, "Invalid string\n");
        return EXIT_FAILURE;
    }

    printf("Sum of ASCII values: %ld\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}