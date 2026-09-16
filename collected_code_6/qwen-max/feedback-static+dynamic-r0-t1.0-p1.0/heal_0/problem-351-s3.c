#include <stdio.h>
#include <stdlib.h>

int findFirstKTimes(int *arr, int n, int k) {
    int *count = (int *)calloc(n, sizeof(int));
    if (count == NULL) {
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
        if (count[arr[i]] == k) {
            free(count);
            return arr[i];
        }
    }
    
    free(count);
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    int result = findFirstKTimes(arr, n, k);
    if (result != -1) {
        printf("First element occurring %d times: %d\n", k, result);
    } else {
        printf("No element occurs %d times in the array.\n", k);
    }
    return 0;
}