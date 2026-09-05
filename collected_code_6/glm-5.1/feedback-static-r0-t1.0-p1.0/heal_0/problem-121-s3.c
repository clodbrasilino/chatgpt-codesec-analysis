#include <stdio.h>
#include <stdlib.h>

void find_triplet(int *arr, int n, int target) {
    if (arr == NULL || n < 3) {
        return;
    }

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (arr[i] + arr[j] + arr[k] == target) {
                    printf("%d %d %d\n", arr[i], arr[j], arr[k]);
                    return;
                }
            }
        }
    }
}

int main(void) {
    int arr[] = {1, 4, 45, 6, 10, 8};
    int target = 22;
    int n = sizeof(arr) / sizeof(arr[0]);

    find_triplet(arr, n, target);

    return 0;
}