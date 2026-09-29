#include <stdio.h>

int count_same_pairs(int arr1[], int arr2[], int arr3[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if(arr1[i] == arr2[j] && arr2[j] == arr3[k]) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 3, 4, 5, 6};
    int arr3[] = {3, 4, 5, 6, 7};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    printf("Count of same pairs: %d", count_same_pairs(arr1, arr2, arr3, n));

    return 0;
}