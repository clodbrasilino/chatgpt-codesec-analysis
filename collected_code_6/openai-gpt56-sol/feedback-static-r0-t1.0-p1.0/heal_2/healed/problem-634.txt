#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_even(uint32_t n, uint64_t *result)
{
    const uint32_t limit = UINT32_C(249);
    uint64_t sum = UINT64_C(0);

    if (result == NULL || n > limit) {
        return -1;
    }

    for (uint64_t i = UINT64_C(1); i <= n; ++i) {
        const uint64_t even = UINT64_C(2) * i;
        const uint64_t square = even * even;
        sum += square * square;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t value;
    uint64_t sum;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && input[length - 1] != '\n' && !feof(stdin)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT32_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_fourth_powers_even((uint32_t)value, &sum) != 0) {
        free(input);
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}