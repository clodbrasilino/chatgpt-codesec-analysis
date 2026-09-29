#include <errno.h>
#include <limits.h>
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

int main(int argc, const char *const argv[])
{
    char *end = NULL;
    long parsed;
    int target;
    const int values[] = {1, 2, 2, 4, 7, 7, 9};
    const size_t count = sizeof(values) / sizeof(values[0]);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtol(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        parsed < INT_MIN ||
        parsed > INT_MAX) {
        fprintf(stderr, "Invalid integer: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    target = (int)parsed;
    printf("%zu\n", right_insertion_point(values, count, target));

    return EXIT_SUCCESS;
}