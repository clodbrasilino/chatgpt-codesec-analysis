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

    if (str == NULL) {
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
    char buffer[BUFFER_SIZE];
    unsigned long result;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = count_substrings(buffer, sizeof(buffer));

    if (printf("%lu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}