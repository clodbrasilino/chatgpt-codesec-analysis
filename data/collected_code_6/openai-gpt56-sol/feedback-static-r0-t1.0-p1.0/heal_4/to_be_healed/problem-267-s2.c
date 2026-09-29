#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_odd_squares(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > UINT64_C(3024616)) {
        return 0;
    }

    a = n;
    b = UINT64_C(2) * n - UINT64_C(1);
    c = UINT64_C(2) * n + UINT64_C(1);

    if (a % UINT64_C(3) == 0) {
        a /= UINT64_C(3);
    } else if (b % UINT64_C(3) == 0) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    *result = a * b * c;
    return 1;
}

static int read_line(char *buffer, size_t size)
{
    size_t length;
    int ch;

    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return 0;
    }

    for (length = 0; length < size && buffer[length] != '\0'; ++length) {
        if (buffer[length] == '\n') {
            return 1;
        }
    }

    if (length < size - 1 || feof(stdin)) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t input;
    uint64_t result;

    if (!read_line(buffer, sizeof buffer)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || input > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || buffer[0] == '-') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_of_odd_squares((uint64_t)input, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}