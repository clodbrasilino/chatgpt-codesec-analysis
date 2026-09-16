#include <stdio.h>
#include <stddef.h>

int frequency_of_smallest(const int *arr, size_t size, size_t *frequency)
{
    size_t i;
    int min_value;
    size_t count;

    if (arr == NULL || frequency == NULL || size == 0U) {
        return -1;
    }

    min_value = arr[0];
    count = 1U;

    for (i = 1U; i < size; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
            count = 1U;
        } else if (arr[i] == min_value) {
            count++;
        }
    }

    *frequency = count;
    return 0;
}

int main(void)
{
    int data[] = { 5, 2, 8, 2, 9, 2, 7 };
    size_t size = sizeof(data) / sizeof(data[0]);
    size_t freq = 0U;

    if (frequency_of_smallest(data, size, &freq) != 0) {
        if (fprintf(stderr, "Error: invalid input\n") < 0) {
            return 1;
        }
        return 1;
    }

    if (printf("Frequency of smallest value: %zu\n", freq) < 0) {
        return 1;
    }

    return 0;
}