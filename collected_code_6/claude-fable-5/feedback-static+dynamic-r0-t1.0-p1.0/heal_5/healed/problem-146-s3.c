#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    size_t len;

    printf("Enter a string: ");

    read_len = getline(&buffer, &buffer_size, stdin);
    if (read_len < 0) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    len = (size_t)read_len;
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    result = ascii_sum(buffer, len + 1);
    if (result < 0) {
        fprintf(stderr, "Invalid string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Total ASCII value: %ld\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}