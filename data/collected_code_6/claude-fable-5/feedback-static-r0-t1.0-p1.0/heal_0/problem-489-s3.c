#include <stdio.h>
#include <stdlib.h>

int frequency_of_largest(const int *arr, size_t size, int *frequency)
{
    size_t i;
    int max;
    int count;

    if (arr == NULL || size == 0 || frequency == NULL) {
        return -1;
    }

    max = arr[0];
    count = 1;

    for (i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
            count = 1;
        } else if (arr[i] == max) {
            count++;
        }
    }

    *frequency = count;
    return 0;
}

int main(void)
{
    int data[] = {3, 7, 1, 7, 4, 7, 2};
    size_t size = sizeof(data) / sizeof(data[0]);
    int freq;

    if (frequency_of_largest(data, size, &freq) != 0) {
        fprintf(stderr, "Error: invalid input to frequency_of_largest\n");
        return EXIT_FAILURE;
    }

    printf("Frequency of the largest value: %d\n", freq);
    return EXIT_SUCCESS;
}