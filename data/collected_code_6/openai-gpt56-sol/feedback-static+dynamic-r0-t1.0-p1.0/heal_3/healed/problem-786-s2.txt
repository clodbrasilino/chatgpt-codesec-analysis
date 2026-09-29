#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t right_insertion_point(const int *values, size_t count, int target)
{
    size_t left = 0;
    size_t right = count;

    while (left < right) {
        const size_t middle = left + (right - left) / 2;

        if (values[middle] <= target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }

    return left;
}

int main(int argc, char *argv[])
{
    int *values = NULL;
    size_t count;
    char *end;
    unsigned long long parsed_count;
    long parsed_target;
    size_t insertion_point;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <count> <sorted values...> <target>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_count = strtoull(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || argv[1][0] == '-' ||
        parsed_count > SIZE_MAX / sizeof(*values) ||
        parsed_count != (unsigned long long)(argc - 3)) {
        fprintf(stderr, "Invalid count\n");
        return EXIT_FAILURE;
    }

    count = (size_t)parsed_count;

    if (count > 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        long parsed_value;

        errno = 0;
        parsed_value = strtol(argv[i + 2], &end, 10);

        if (errno != 0 || end == argv[i + 2] || *end != '\0' ||
            parsed_value < INT_MIN || parsed_value > INT_MAX) {
            fprintf(stderr, "Invalid value\n");
            free(values);
            return EXIT_FAILURE;
        }

        values[i] = (int)parsed_value;

        if (i > 0 && values[i] < values[i - 1]) {
            fprintf(stderr, "Values must be sorted\n");
            free(values);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    parsed_target = strtol(argv[count + 2], &end, 10);

    if (errno != 0 || end == argv[count + 2] || *end != '\0' ||
        parsed_target < INT_MIN || parsed_target > INT_MAX) {
        fprintf(stderr, "Invalid target\n");
        free(values);
        return EXIT_FAILURE;
    }

    insertion_point =
        right_insertion_point(values, count, (int)parsed_target);

    printf("%zu\n", insertion_point);

    free(values);
    return EXIT_SUCCESS;
}