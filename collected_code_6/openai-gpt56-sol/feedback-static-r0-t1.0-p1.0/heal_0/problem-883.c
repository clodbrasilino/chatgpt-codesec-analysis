#include <stdio.h>
#include <stdlib.h>

static int print_divisible_numbers(const int *numbers, size_t count, int m, int n)
{
    size_t i;

    if (numbers == NULL || m == 0 || n == 0) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            if (printf("%d\n", numbers[i]) < 0) {
                return -1;
            }
        }
    }

    return 0;
}

int main(void)
{
    const int numbers[] = {12, 18, 24, 30, 36, 42, 48, 60, 72};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    const int m = 3;
    const int n = 4;

    if (print_divisible_numbers(numbers, count, m, n) != 0) {
        if (fprintf(stderr, "Unable to process the numbers.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}