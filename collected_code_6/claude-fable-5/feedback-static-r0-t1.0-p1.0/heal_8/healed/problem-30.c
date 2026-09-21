#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

long long countSubstrings(const char *str, size_t max_len)
{
    long long counts[256] = {0};
    long long result = 0;
    size_t i;
    size_t len;

    if (str == NULL) {
        return 0;
    }

    len = strnlen(str, max_len);

    for (i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    for (i = 0; i < 256; i++) {
        result += (counts[i] * (counts[i] + 1)) / 2;
    }

    return result;
}

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;
    size_t len;
    long long result;

    printf("Enter a string: ");

    nread = getline(&buffer, &bufsize, stdin);
    if (nread < 0) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    len = strnlen(buffer, (size_t)nread);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len >= MAX_INPUT_SIZE) {
        buffer[MAX_INPUT_SIZE - 1] = '\0';
        len = MAX_INPUT_SIZE - 1;
    }

    result = countSubstrings(buffer, len);

    free(buffer);
    buffer = NULL;

    if (printf("Count of substrings: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}