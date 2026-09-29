#include <stdio.h>
#include <stdlib.h>

static int is_odd(int value)
{
    return value % 2 != 0;
}

static int print_odd_numbers(const int *numbers, size_t count)
{
    if (numbers == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (is_odd(numbers[i])) {
            if (printf("%d\n", numbers[i]) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const int numbers[] = {12, -5, 8, 7, 0, 19, -22, -3, 14, 11};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (print_odd_numbers(numbers, count) != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}