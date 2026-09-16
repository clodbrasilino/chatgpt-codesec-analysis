#include <stdio.h>
#include <stdlib.h>

static int find_first_odd(const int *numbers, size_t count, int *result)
{
    if (numbers == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (numbers[i] % 2 != 0) {
            *result = numbers[i];
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    int numbers[] = {2, 4, 6, 7, 8, 9};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int first_odd = 0;

    if (find_first_odd(numbers, count, &first_odd)) {
        if (printf("%d\n", first_odd) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No odd number found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}