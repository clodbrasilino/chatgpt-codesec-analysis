#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int maxDifference(int arr[], int n) {
    if (n < 2) {
        return 0;
    }

    int min_element = arr[0];
    int max_diff = arr[1] - arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] - min_element > max_diff) {
            max_diff = arr[i] - min_element;
        }
        if (arr[i] < min_element) {
            min_element = arr[i];
        }
    }

    return max_diff;
}

int main(void) {
    int n;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    int result = maxDifference(arr, n);
    printf("Maximum difference: %d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}