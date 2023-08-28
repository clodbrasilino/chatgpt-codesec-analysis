#include <stdio.h>
#include <stdlib.h>

void convertToFloat(float* arr, int len) {
    for (int i = 0; i < len; i++) {
        arr[i] = (float) arr[i];
    }
}

int main() {
    // Example usage
    int len = 5;
    int arr[] = {1, 2, 3, 4, 5};

    convertToFloat(arr, len);

    for (int i = 0; i < len; i++) {
        printf("%.2f ", arr[i]);
    }

    return 0;
}