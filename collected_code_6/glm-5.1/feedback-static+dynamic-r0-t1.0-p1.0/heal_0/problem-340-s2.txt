#include <stdio.h>
#include <stdlib.h>

int sum_three_lowest_positive(const int *arr, size_t size) {
    if (arr == NULL || size < 3) {
        return 0;
    }

    int min1 = -1;
    int min2 = -1;
    int min3 = -1;

    for (size_t i = 0; i < size; ++i) {
        if (arr[i] > 0) {
            if (min1 == -1 || arr[i] < min1) {
                min3 = min2;
                min2 = min1;
                min1 = arr[i];
            } else if (min2 == -1 || arr[i] < min2) {
                min3 = min2;
                min2 = arr[i];
            } else if (min3 == -1 || arr[i] < min3) {
                min3 = arr[i];
            }
        }
    }

    if (min3 == -1) {
        return 0;
    }

    return min1 + min2 + min3;
}

int main(void) {
    int data[] = {4, 5, 1, 8, -2, 3, 6, -1};
    size_t data_size = sizeof(data) / sizeof(data[0]);

    int result = sum_three_lowest_positive(data, data_size);
    
    printf("%d\n", result);

    return 0;
}