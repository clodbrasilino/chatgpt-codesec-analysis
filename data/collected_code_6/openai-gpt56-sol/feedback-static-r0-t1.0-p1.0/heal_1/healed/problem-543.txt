#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int add_int64(int64_t a, int64_t b, int64_t *sum)
{
    if (sum == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *sum = a + b;
    return 1;
}

static size_t digit_count(int64_t value)
{
    uint64_t magnitude;
    size_t count = 1U;

    if (value < 0) {
        magnitude = (uint64_t)(-(value + 1)) + UINT64_C(1);
    } else {
        magnitude = (uint64_t)value;
    }

    while (magnitude >= UINT64_C(10)) {
        magnitude /= UINT64_C(10);
        ++count;
    }

    return count;
}

int main(void)
{
    char input[256];
    char trailing;
    int64_t first;
    int64_t second;
    int64_t sum;

    if (fputs("Enter two integers: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input, " %" SCNd64 " %" SCNd64 " %c",
               &first, &second, &trailing) != 2) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!add_int64(first, second, &sum)) {
        fputs("Integer overflow.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRId64 "\nDigits: %zu\n",
               sum, digit_count(sum)) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}