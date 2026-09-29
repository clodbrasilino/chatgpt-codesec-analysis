#include <stdio.h>
#include <stdlib.h>

int findSmallestMissing(const int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] != i) {
            return i;
        }
    }
    return n;
}

int main(void) {
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 9};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));
    int result = findSmallestMissing(arr, n);
    printf("Smallest missing number: %d\n", result);
    return 0;
}