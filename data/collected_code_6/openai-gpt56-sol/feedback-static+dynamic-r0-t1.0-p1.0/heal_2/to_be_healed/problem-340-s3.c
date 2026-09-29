#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <limits.h>

static int read_size(size_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char extra;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    if (sscanf(buffer, " %" SCNuMAX " %c", &parsed, &extra) != 1 ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char extra;
    int64_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    if (sscanf(buffer, " %" SCNd64 " %c", &parsed, &extra) != 1) {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int sum_three_lowest_positive(const int64_t *numbers,
                                     size_t count,
                                     int64_t *sum)
{
    if (sum == NULL || (numbers == NULL && count != 0)) {
        return -1;
    }

    int64_t lowest[3] = { INT64_MAX, INT64_MAX, INT64_MAX };
    size_t positives = 0;

    for (size_t i = 0; i < count; ++i) {
        int64_t value = numbers[i];

        if (value <= 0) {
            continue;
        }

        if (positives < 3) {
            ++positives;
        }

        if (value < lowest[0]) {
            lowest[2] = lowest[1];
            lowest[1] = lowest[0];
            lowest[0] = value;
        } else if (value < lowest[1]) {
            lowest[2] = lowest[1];
            lowest[1] = value;
        } else if (value < lowest[2]) {
            lowest[2] = value;
        }
    }

    if (positives < 3) {
        return 1;
    }

    if (lowest[0] > INT64_MAX - lowest[1]) {
        return 2;
    }

    int64_t partial = lowest[0] + lowest[1];

    if (partial > INT64_MAX - lowest[2]) {
        return 2;
    }

    *sum = partial + lowest[2];
    return 0;
}

int main(void)
{
    size_t count;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *numbers = NULL;

    if (count != 0) {
        numbers = malloc(count * sizeof *numbers);
        if (numbers == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&numbers[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int64_t sum;
    int result = sum_three_lowest_positive(numbers, count, &sum);

    free(numbers);

    if (result == 1) {
        fputs("Fewer than three positive numbers\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == 2) {
        fputs("Sum overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (result != 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}