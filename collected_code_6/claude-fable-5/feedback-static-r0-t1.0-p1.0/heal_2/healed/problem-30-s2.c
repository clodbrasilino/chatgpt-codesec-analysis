#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

unsigned long count_substrings(const char *str, size_t max_len)
{
    unsigned long counts[256];
    unsigned long total;
    size_t i;
    size_t len;

    if (str == NULL || max_len == 0) {
        return 0UL;
    }

    memset(counts, 0, sizeof(counts));

    len = strnlen(str, max_len);

    for (i = 0; i < len; i++) {
        counts[(unsigned char)str[i]]++;
    }

    total = 0UL;
    for (i = 0; i < 256; i++) {
        total += (counts[i] * (counts[i] + 1UL)) / 2UL;
    }

    return total;
}

int main(void)
{
    char *buffer;
    unsigned long result;
    size_t len;

    buffer = calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    buffer[BUFFER_SIZE - 1] = '\0';

    len = strnlen(buffer, BUFFER_SIZE);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = count_substrings(buffer, BUFFER_SIZE);

    if (printf("%lu\n", result) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}