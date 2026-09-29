#include <stdio.h>
#include <stdlib.h>

static int print_positive_numbers(const int *numbers, size_t count)
{
    if (numbers == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (numbers[i] > 0) {
            if (printf("%d\n", numbers[i]) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const int numbers[] = {-8, 3, 0, 12, -4, 7};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (print_positive_numbers(numbers, count) != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}