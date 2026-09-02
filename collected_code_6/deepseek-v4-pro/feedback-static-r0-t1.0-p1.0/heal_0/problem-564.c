#include <stdio.h>
#include <stdlib.h>

int count_unequal_pairs(int *arr, int n) {
    if (arr == NULL || n <= 1) {
        return 0;
    }

    int total_pairs = n * (n - 1) / 2;
    int equal_pairs = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                equal_pairs++;
            }
        }
    }

    return total_pairs - equal_pairs;
}

int main(void) {
    int arr[] = {1, 2, 3, 1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = count_unequal_pairs(arr, n);
    printf("%d\n", result);

    return 0;
}