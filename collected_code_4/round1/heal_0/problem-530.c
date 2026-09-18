#include <stdio.h>

double ratio_of_negative_numbers(int arr[], int size) {
    if (size == 0) {
        return 0.0;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            count++;
        }
    }

    return (double)count / size;
}

int main() {
    int arr[] = {-5, 2, -3, 18, -1, 6, -9};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("The ratio of negative numbers is: %.2f", ratio_of_negative_numbers(arr, size));

    return 0;
}