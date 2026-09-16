#include <stdio.h>
#include <stddef.h>

double get_negative_ratio(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0.0;
    }

    size_t negative_count = 0;

    for (size_t i = 0; i < size; ++i) {
        if (arr[i] < 0) {
            negative_count++;
        }
    }

    return (double)negative_count / size;
}

int main(void) {
    int arr[] = {1, -2, 3, -4, 5, -6, -7, 8, 9, 0};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    double ratio = get_negative_ratio(arr, size);

    printf("%.2f\n", ratio);

    return 0;
}