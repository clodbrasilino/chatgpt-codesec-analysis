#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_smart_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == 0 || n > 64) {
        return 0;
    }

    *result = UINT64_C(1) << (n - 1);
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] != '\n' && !feof(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' ||
        !nth_smart_number((uint64_t)parsed, &result)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}