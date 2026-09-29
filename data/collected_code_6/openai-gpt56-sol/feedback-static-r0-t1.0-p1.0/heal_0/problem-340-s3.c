#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int sum_three_lowest_positive(const int64_t *numbers, size_t count, int64_t *sum)
{
    if (numbers == NULL || sum == NULL) {
        return -1;
    }

    int64_t lowest[3] = {INT64_MAX, INT64_MAX, INT64_MAX};
    size_t positives = 0;

    for (size_t i = 0; i < count; ++i) {
        int64_t value = numbers[i];

        if (value <= 0) {
            continue;
        }

        ++positives;

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

    if (lowest[0] > INT64_MAX - lowest[1] ||
        lowest[0] + lowest[1] > INT64_MAX - lowest[2]) {
        return 2;
    }

    *sum = lowest[0] + lowest[1] + lowest[2];
    return 0;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1 || count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *numbers = NULL;

    if (count > 0) {
        numbers = malloc(count * sizeof(*numbers));
        if (numbers == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%" SCNd64, &numbers[i]) != 1) {
            fputs("Invalid input\n", stderr);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int64_t sum = 0;
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