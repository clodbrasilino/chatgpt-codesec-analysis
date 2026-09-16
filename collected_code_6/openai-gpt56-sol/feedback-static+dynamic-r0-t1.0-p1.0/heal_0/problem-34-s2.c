#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

static bool find_missing_number(const int array[], size_t length, int *missing)
{
    if (array == NULL || missing == NULL || length == 0U) {
        return false;
    }

    for (size_t i = 1U; i < length; ++i) {
        if (array[i] <= array[i - 1U]) {
            return false;
        }

        if (array[i] - array[i - 1U] == 2) {
            *missing = array[i - 1U] + 1;
            return true;
        }

        if (array[i] - array[i - 1U] > 2) {
            return false;
        }
    }

    return false;
}

int main(void)
{
    const int numbers[] = {1, 2, 3, 4, 6, 7, 8};
    const size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int missing = 0;

    if (!find_missing_number(numbers, length, &missing)) {
        (void)fprintf(stderr, "Unable to determine the missing number.\n");
        return 1;
    }

    if (printf("Missing number: %d\n", missing) < 0) {
        return 1;
    }

    return 0;
}