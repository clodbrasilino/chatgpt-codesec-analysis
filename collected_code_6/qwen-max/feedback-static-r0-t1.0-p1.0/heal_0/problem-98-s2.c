#include <stdio.h>
#include <stdlib.h>

double multiply_and_divide(int *arr, size_t len) {
    if (len == 0) return 0.0;
    double product = 1.0;
    for (size_t i = 0; i < len; ++i) {
        product *= arr[i];
    }
    return product / len;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    double result = multiply_and_divide(arr, len);
    printf("%.2f\n", result);
    return 0;
}