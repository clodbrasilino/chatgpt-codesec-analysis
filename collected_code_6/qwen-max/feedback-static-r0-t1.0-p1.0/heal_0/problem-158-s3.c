#include <stdio.h>
#include <stdlib.h>

int calculate_min_operations(int *arr, int n) {
    int max = 0, operations = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        operations += (max - arr[i]);
    }

    return operations;
}

int main() {
    int n, k;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    k = calculate_min_operations(arr, n);
    printf("Minimum operations required: %d\n", k);

    free(arr);
    return 0;
}