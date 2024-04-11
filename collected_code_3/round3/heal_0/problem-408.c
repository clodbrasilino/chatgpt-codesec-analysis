#include <stdio.h>
#include <stdlib.h>

void findPairs(int arr1[], int arr2[], int n, int m, int k) {
    int i = 0, j = 0;
    while (i < n && j < m && k > 0) {
        printf("(%d, %d)\n", arr1[i], arr2[j]);
        j++;
        if (j == m) {
            i++;
            j = 0;
        }
        k--;
    }
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {6, 7, 8, 9, 10};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int m = sizeof(arr2) / sizeof(arr2[0]);
    int k = 5;
    findPairs(arr1, arr2, n, m, k);
    return 0;
}