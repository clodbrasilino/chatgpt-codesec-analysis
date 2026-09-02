#include <stdio.h>
#include <stdlib.h>

long long productOfNonRepeated(int *arr, int n) {
    int *frequency = (int *)calloc(n, sizeof(int));
    long long product = 1;
    for (int i = 0; i < n; ++i) {
        frequency[arr[i]]++;
    }
    for (int i = 0; i < n; ++i) {
        if (frequency[arr[i]] == 1) {
            product *= arr[i];
        }
    }
    free(frequency);
    return product;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%lld\n", productOfNonRepeated(arr, n));
    return 0;
}