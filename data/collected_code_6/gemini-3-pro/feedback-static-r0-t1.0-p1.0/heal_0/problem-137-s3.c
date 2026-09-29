#include <stdio.h>
#include <stdlib.h>

double find_zero_ratio(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0.0;
    }

    size_t zero_count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (array[i] == 0) {
            zero_count++;
        }
    }

    return (double)zero_count / (double)size;
}

int main(void) {
    int my_array[] = {1, 0, 3, 0, 5, 0, 0, 8, 9};
    size_t array_size = sizeof(my_array) / sizeof(my_array[0]);

    double ratio = find_zero_ratio(my_array, array_size);
    printf("Ratio of zeroes: %f\n", ratio);

    double empty_ratio = find_zero_ratio(NULL, 0);
    printf("Ratio of zeroes in empty array: %f\n", empty_ratio);

    return 0;
}