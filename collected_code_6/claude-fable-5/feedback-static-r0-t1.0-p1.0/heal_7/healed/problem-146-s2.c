#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    size_t bufsize = 0;
    ssize_t nread;
    long result;

    printf("Enter a string: ");

    nread = getline(&buffer, &bufsize, stdin);
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    if (nread > 0 && buffer[nread - 1] == '\n') {
        buffer[nread - 1] = '\0';
        nread--;
    }

    result = ascii_sum(buffer, (size_t)nread + 1);
    if (result < 0) {
        fprintf(stderr, "Invalid string\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("Sum of ASCII values: %ld\n", result);

    free(buffer);
    return EXIT_SUCCESS;
}