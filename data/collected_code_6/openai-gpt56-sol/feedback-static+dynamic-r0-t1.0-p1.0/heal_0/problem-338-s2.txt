#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

static int count_substrings(const char *str, uint64_t *result)
{
    if (str == NULL || result == NULL) {
        return -1;
    }

    uint64_t frequencies[UCHAR_MAX + 1] = {0};
    uint64_t total = 0;

    for (const unsigned char *p = (const unsigned char *)str; *p != '\0'; ++p) {
        if (frequencies[*p] == UINT64_MAX ||
            total > UINT64_MAX - frequencies[*p] - 1U) {
            return -1;
        }

        total += frequencies[*p] + 1U;
        ++frequencies[*p];
    }

    *result = total;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[length - 1] = '\0';
    }

    uint64_t result = 0;

    if (count_substrings(line, &result) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}