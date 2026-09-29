#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool find_first_duplicate(const int *arr, size_t size, int *result)
{
    if (arr == NULL || result == NULL || size < 2U) {
        return false;
    }

    for (size_t i = 1U; i < size; i++) {
        for (size_t j = 0U; j < i; j++) {
            if (arr[i] == arr[j]) {
                *result = arr[i];
                return true;
            }
        }
    }

    return false;
}

int main(void)
{
    int numbers[] = { 4, 7, 2, 9, 7, 4, 1 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int duplicate = 0;

    if (find_first_duplicate(numbers, count, &duplicate)) {
        if (printf("First duplicate: %d\n", duplicate) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No duplicate found.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}