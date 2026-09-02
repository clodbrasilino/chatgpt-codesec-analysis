#include <stdio.h>
#include <stdlib.h>

int count_self_inverse(const int arr[], int n, int p) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] <= 0 || arr[i] >= p) {
            continue;
        }
        if ((arr[i] * arr[i]) % p == 1) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int p = 7;

    int result = count_self_inverse(arr, n, p);
    printf("%d\n", result);

    return 0;
}