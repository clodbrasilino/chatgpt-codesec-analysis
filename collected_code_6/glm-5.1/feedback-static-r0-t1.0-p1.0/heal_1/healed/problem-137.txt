#include <stdio.h>
#include <stdlib.h>

double find_zero_ratio(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0.0;
    }

    size_t zero_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] == 0) {
            zero_count++;
        }
    }

    return (double)zero_count / (double)size;
}

int main(void) {
    int arr1[] = {0, 1, 2, 0, 4, 0};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    double ratio1 = find_zero_ratio(arr1, size1);
    printf("Ratio 1: %f\n", ratio1);

    int arr2[] = {1, 2, 3, 4, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    double ratio2 = find_zero_ratio(arr2, size2);
    printf("Ratio 2: %f\n", ratio2);

    int arr3[] = {0, 0, 0};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    double ratio3 = find_zero_ratio(arr3, size3);
    printf("Ratio 3: %f\n", ratio3);

    double ratio4 = find_zero_ratio(NULL, 5);
    printf("Ratio 4 (NULL array): %f\n", ratio4);

    const int arr5[] = {1, 2, 3};
    double ratio5 = find_zero_ratio(arr5, 0);
    printf("Ratio 5 (Zero size): %f\n", ratio5);

    return 0;
}