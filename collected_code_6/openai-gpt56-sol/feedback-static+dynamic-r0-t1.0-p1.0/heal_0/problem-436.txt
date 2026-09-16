#include <stdio.h>
#include <stdlib.h>

static int print_negative_numbers(const int *numbers, size_t count)
{
    if (numbers == NULL && count != 0U) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (numbers[i] < 0 && printf("%d\n", numbers[i]) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const int numbers[] = {12, -7, 0, -3, 25, -18};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);

    if (print_negative_numbers(numbers, count) != 0) {
        (void)fprintf(stderr, "Failed to print negative numbers.\n");
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        (void)fprintf(stderr, "Failed to flush output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}