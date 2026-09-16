#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int find_first_even(const long *numbers, size_t count, long *result)
{
    if (numbers == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 == 0) {
            *result = numbers[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    size_t count = 0;

    if (scanf("%zu", &count) != 1 || count == 0 ||
        count > SIZE_MAX / sizeof(long)) {
        return EXIT_FAILURE;
    }

    long *numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%ld", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    long result = 0;
    int status = find_first_even(numbers, count, &result);

    free(numbers);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status == 1) {
        if (printf("%ld\n", result) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No even number found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}