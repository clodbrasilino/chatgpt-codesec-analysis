#include <stdio.h>
#include <stdlib.h>

int find_smallest(const int *numbers, size_t count, int *smallest)
{
    if (numbers == NULL || smallest == NULL || count == 0U) {
        return -1;
    }

    *smallest = numbers[0];

    for (size_t i = 1U; i < count; ++i) {
        if (numbers[i] < *smallest) {
            *smallest = numbers[i];
        }
    }

    return 0;
}

int main(void)
{
    int numbers[] = {42, 17, -3, 8, 0, 29};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int smallest = 0;

    if (find_smallest(numbers, count, &smallest) != 0) {
        (void)fprintf(stderr, "Unable to find the smallest number.\n");
        return EXIT_FAILURE;
    }

    if (printf("Smallest number: %d\n", smallest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}