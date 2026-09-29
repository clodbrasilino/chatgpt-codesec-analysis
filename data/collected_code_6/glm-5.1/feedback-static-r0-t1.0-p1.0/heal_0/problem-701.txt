#include <stdio.h>
#include <stdlib.h>

int find_equilibrium_index(int *arr, int n) {
    if (arr == NULL || n <= 0) {
        return -1;
    }

    long long total_sum = 0;
    long long left_sum = 0;

    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }

    for (int i = 0; i < n; i++) {
        long long right_sum = total_sum - left_sum - arr[i];
        if (left_sum == right_sum) {
            return i;
        }
        left_sum += arr[i];
    }

    return -1;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    int n = argc - 1;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int result = find_equilibrium_index(arr, n);
    printf("%d\n", result);

    free(arr);
    arr = NULL;

    return 0;
}