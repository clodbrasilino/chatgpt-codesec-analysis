#include <stdio.h>

int countNegatives(const int arr[], int size) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            count++;
        }
    }

    return count;
}

int main() {
    int arr[] = {-1, -2, 3, 4, -5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    int negativeCount = countNegatives(arr, size);

    printf("%d\n", negativeCount);

    return 0;
}