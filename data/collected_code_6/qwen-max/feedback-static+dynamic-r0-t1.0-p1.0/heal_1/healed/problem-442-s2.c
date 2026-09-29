#include <stdio.h>
#include <stddef.h>

double findPositiveRatio(const int *arr, size_t len) {
    if (len == 0) return 0.0;
    int positiveCount = 0;
    for (size_t i = 0; i < len; ++i) {
        if (arr[i] > 0) {
            positiveCount++;
        }
    }
    return (double)positiveCount / len;
}

int main() {
    int arr[] = {1, -2, 3, 4, -5, 6, 7, -8, 9, 10};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    double ratio = findPositiveRatio(arr, len);
    printf("The ratio of positive numbers: %.2f\n", ratio);
    return 0;
}