#include <stdio.h>

int count_same_pairs(int arr1[], int arr2[], int n, int m) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(arr1[i] == arr2[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 3, 4, 5, 6};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);
    printf("Count of same pairs: %d\n", count_same_pairs(arr1, arr2, n, m));
    return 0;
}