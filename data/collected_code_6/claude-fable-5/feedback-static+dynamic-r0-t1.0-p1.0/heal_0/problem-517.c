#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool find_largest_positive(const int *list, size_t size, int *result)
{
    bool found = false;
    int largest = 0;

    if ((list == NULL) || (result == NULL) || (size == 0U)) {
        return false;
    }

    for (size_t i = 0U; i < size; i++) {
        if (list[i] > 0) {
            if ((!found) || (list[i] > largest)) {
                largest = list[i];
                found = true;
            }
        }
    }

    if (found) {
        *result = largest;
    }

    return found;
}

int main(void)
{
    int numbers[] = { -5, 12, 7, -3, 42, 0, 19 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int largest = 0;

    if (find_largest_positive(numbers, count, &largest)) {
        if (printf("Largest positive number: %d\n", largest) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No positive number found in the list.\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}