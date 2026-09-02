#include <stdio.h>

int equilibrium_index(const int arr[], int n) {
    int total_sum = 0;
    int left_sum = 0;
    int i;

    if (n <= 0 || arr == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    for (i = 0; i < n; i++) {
        total_sum -= arr[i];

        if (left_sum == total_sum) {
            return i;
        }

        left_sum += arr[i];
    }

    return -1;
}

int main(void) {
    int arr[] = {-7, 1, 5, 2, -4, 3, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = equilibrium_index(arr, n);

    if (result != -1) {
        printf("Equilibrium index: %d\n", result);
    } else {
        printf("No equilibrium index found\n");
    }

    return 0;
}