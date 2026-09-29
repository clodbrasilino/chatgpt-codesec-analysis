#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int count_tilings(size_t n, uint64_t *result)
{
    uint64_t previous = 1;
    uint64_t current = 1;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 2; i <= n; ++i) {
        if (UINT64_MAX - current < previous) {
            return -1;
        }

        uint64_t next = current + previous;
        previous = current;
        current = next;
    }

    *result = current;
    return 0;
}

static int read_input(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    unsigned long long input;
    ssize_t length;

    if (value == NULL) {
        return -1;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return -1;
    }

    if (ferror(stdin)) {
        free(line);
        return -1;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    errno = 0;
    end = NULL;
    input = strtoull(line, &end, 10);

    if (errno == ERANGE || end == line) {
        free(line);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || input > SIZE_MAX) {
        free(line);
        return -1;
    }

    *value = (size_t)input;
    free(line);
    return 0;
}

int main(void)
{
    size_t input;
    uint64_t result;

    if (read_input(&input) != 0) {
        return EXIT_FAILURE;
    }

    if (count_tilings(input, &result) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}