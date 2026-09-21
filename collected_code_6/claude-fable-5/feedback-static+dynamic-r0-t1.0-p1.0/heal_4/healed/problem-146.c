#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 256

long ascii_sum(const char *str, size_t max_len)
{
    long sum = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        sum += (unsigned char)str[i];
    }

    return sum;
}

int main(void)
{
    char *buffer = NULL;
    size_t buf_size = 0;
    ssize_t nread;
    long result;

    printf("Enter a string: ");

    nread = getline(&buffer, &buf_size, stdin);
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (nread > 0 && buffer[nread - 1] == '\n') {
        buffer[nread - 1] = '\0';
        nread--;
    }

    if ((size_t)nread >= MAX_INPUT_LEN) {
        fprintf(stderr, "Input too long\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    result = ascii_sum(buffer, MAX_INPUT_LEN);
    if (result < 0) {
        fprintf(stderr, "Invalid string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Sum of ASCII values: %ld\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}