#include <stdio.h>
#include <stdbool.h>

bool isSubArray(int arr1[], int arr2[], int m, int n) {
    int i = 0;
    int j = 0;
    while (i < n && j < m) {
        if (arr1[i] == arr2[j]) {
            i++;
            j++;
            if (j == m)
                return true;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    return false;
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arr2[] = {3, 4, 5};
    int m = sizeof(arr2)/sizeof(arr2[0]);
    int n = sizeof(arr1)/sizeof(arr1[0]);

    if (isSubArray(arr1, arr2, m, n))
        printf("Array2 is a subarray of Array1\n");
    else
        printf("Array2 is not a subarray of Array1\n");

    return 0;
}