#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int sum_range(const int *numbers, size_t length, size_t start,
                     size_t end, int64_t *result)
{
    int64_t sum = 0;

    if (numbers == NULL || result == NULL || start > end || end >= length) {
        return -1;
    }

    for (size_t i = start; i <= end; ++i) {
        sum += numbers[i];
    }

    *result = sum;
    return 0;
}

int main(void)
{
    int numbers[] = {10, 20, 30, 40, 50};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    char input[128];
    size_t start;
    size_t end;
    int64_t result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    if (sscanf(input, "%zu %zu", &start, &end) != 2 || errno != 0) {
        fputs("Enter two valid indices.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_range(numbers, length, start, end, &result) != 0) {
        fputs("Invalid range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    return EXIT_SUCCESS;
}