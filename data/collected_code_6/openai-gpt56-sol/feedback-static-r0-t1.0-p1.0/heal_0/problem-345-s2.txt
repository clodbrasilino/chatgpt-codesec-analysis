#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int find_consecutive_differences(const long long *numbers,
                                        size_t count,
                                        long long *differences)
{
    if (numbers == NULL || differences == NULL || count < 2U) {
        return -1;
    }

    for (size_t i = 0U; i < count - 1U; ++i) {
        if (__builtin_sub_overflow(numbers[i + 1U], numbers[i],
                                   &differences[i])) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1 || count < 2U ||
        count > SIZE_MAX / sizeof(long long)) {
        return EXIT_FAILURE;
    }

    long long *numbers = malloc(count * sizeof(*numbers));
    if (numbers == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lld", &numbers[i]) != 1) {
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    size_t difference_count = count - 1U;
    if (difference_count > SIZE_MAX / sizeof(long long)) {
        free(numbers);
        return EXIT_FAILURE;
    }

    long long *differences =
        malloc(difference_count * sizeof(*differences));
    if (differences == NULL) {
        free(numbers);
        return EXIT_FAILURE;
    }

    if (find_consecutive_differences(numbers, count, differences) != 0) {
        free(differences);
        free(numbers);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < difference_count; ++i) {
        if (printf("%lld%c", differences[i],
                   i + 1U == difference_count ? '\n' : ' ') < 0) {
            free(differences);
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    free(differences);
    free(numbers);
    return EXIT_SUCCESS;
}