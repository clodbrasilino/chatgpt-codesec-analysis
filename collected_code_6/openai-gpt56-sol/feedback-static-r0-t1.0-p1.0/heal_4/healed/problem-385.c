#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int perrin(uint64_t n, uint64_t *result)
{
    uint64_t p0 = 3;
    uint64_t p1 = 0;
    uint64_t p2 = 2;

    if (result == NULL) {
        return 0;
    }

    if (n == 0) {
        *result = p0;
        return 1;
    }

    if (n == 1) {
        *result = p1;
        return 1;
    }

    if (n == 2) {
        *result = p2;
        return 1;
    }

    for (uint64_t i = 3; i <= n; ++i) {
        uint64_t next;

        if (UINT64_MAX - p0 < p1) {
            return 0;
        }

        next = p0 + p1;
        p0 = p1;
        p1 = p2;
        p2 = next;
    }

    *result = p2;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;
    uint64_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[--length] = '\0';
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || *end != '\0' ||
        value > UINT64_MAX || input[0] == '-') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (!perrin((uint64_t)value, &result)) {
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}