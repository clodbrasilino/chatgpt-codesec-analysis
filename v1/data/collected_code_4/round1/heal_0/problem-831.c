#include <stdio.h>

int count_pairs(int *arr, int n) {
    int pair_count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] == arr[j]) {
                pair_count++;
            }
        }
    }
    return pair_count;
}

int main() {
    int arr[] = {1, 2, 3, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Number of pairs: %d\n", count_pairs(arr, n));

    return 0;
}