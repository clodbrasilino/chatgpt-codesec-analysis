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
    char buffer[MAX_INPUT_SIZE];
    size_t len;
    long long result;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = countSubstrings(buffer, sizeof(buffer));

    if (printf("Count of substrings: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}