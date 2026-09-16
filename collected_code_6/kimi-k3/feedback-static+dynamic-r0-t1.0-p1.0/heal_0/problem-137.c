#include <stdio.h>
#include <stdlib.h>

double find_zero_ratio(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0.0;
    }
    
    size_t zero_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == 0) {
            zero_count++;
        }
    }
    
    return (double)zero_count / (double)size;
}

int main(void) {
    int arr[] = {1, 0, 3, 0, 5, 0, 7, 8, 0, 10};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    double ratio = find_zero_ratio(arr, size);
    printf("Ratio of zeroes: %.2f\n", ratio);
    
    return 0;
}