#include <stdio.h>
#include <stdlib.h>

int find_second_smallest(const int *arr, size_t n, int *result)
{
    size_t i;
    int smallest;
    int second;
    int found_second = 0;

    if (arr == NULL || result == NULL || n < 2) {
        return -1;
    }

    smallest = arr[0];
    second = arr[0];

    for (i = 1; i < n; i++) {
        if (arr[i] < smallest) {
            second = smallest;
            smallest = arr[i];
            found_second = 1;
        } else if (arr[i] > smallest && (!found_second || arr[i] < second)) {
            second = arr[i];
            found_second = 1;
        }
    }

    if (!found_second) {
        return -1;
    }

    *result = second;
    return 0;
}

int main(void)
{
    int numbers[] = { 34, 15, 88, 2, 7, 15, 2 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int second_smallest;

    if (find_second_smallest(numbers, count, &second_smallest) != 0) {
        fprintf(stderr, "Could not determine the second smallest number.\n");
        return EXIT_FAILURE;
    }

    if (printf("Second smallest number: %d\n", second_smallest) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}