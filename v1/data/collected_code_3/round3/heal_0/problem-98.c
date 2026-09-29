#include <stdio.h>

double multiplyAndDivide(int arr[], int length) {
    int i;
    double product = 1.0;

    for(i = 0; i < length; i++) {
        product *= arr[i];
    }

    return product / length;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int length = sizeof(arr) / sizeof(arr[0]);

    double result = multiplyAndDivide(arr, length);

    printf("Result: %.2f\n", result);

    return 0;
}