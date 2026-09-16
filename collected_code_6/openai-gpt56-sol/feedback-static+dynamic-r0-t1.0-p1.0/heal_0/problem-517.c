#include <stdio.h>
#include <stdlib.h>

static int find_largest_positive(const int *numbers, size_t count, int *result)
{
    if (numbers == NULL || result == NULL || count == 0U) {
        return 0;
    }

    int found = 0;
    int largest = 0;

    for (size_t i = 0U; i < count; ++i) {
        if (numbers[i] > 0 && (!found || numbers[i] > largest)) {
            largest = numbers[i];
            found = 1;
        }
    }

    if (found) {
        *result = largest;
    }

    return found;
}

int main(void)
{
    const int numbers[] = {-12, 7, 0, 42, -3, 19};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int largest = 0;

    if (!find_largest_positive(numbers, count, &largest)) {
        if (fprintf(stderr, "No positive number found.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Largest positive number: %d\n", largest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}