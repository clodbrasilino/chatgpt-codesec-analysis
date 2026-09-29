#include <stdio.h>
#include <stdlib.h>

static void print_divisible(const int *numbers, size_t count, int m, int n)
{
    size_t i;

    if (numbers == NULL || m == 0 || n == 0) {
        return;
    }

    for (i = 0; i < count; ++i) {
        if (numbers[i] % m == 0 && numbers[i] % n == 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main(void)
{
    int numbers[] = {12, 15, 18, 24, 30, 36, 42, 48};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    const int m = 3;
    const int n = 4;

    print_divisible(numbers, count, m, n);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}