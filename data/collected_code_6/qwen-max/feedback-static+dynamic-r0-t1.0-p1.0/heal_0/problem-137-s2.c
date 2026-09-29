#include <stdio.h>

double find_zero_ratio(int arr[], int size) {
    if (size <= 0) return 0.0;

    int zero_count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            zero_count++;
        }
    }

    return (double)zero_count / size;
}

int main() {
    int arr[] = {0, 1, 0, 3, 4, 0, 6, 0};
    int size = sizeof(arr) / sizeof(arr[0]);

    double ratio = find_zero_ratio(arr, size);
    printf("Ratio of zeroes: %.2f\n", ratio);

    return 0;
}