#include <stdio.h>
#include <stdlib.h>

int sum_non_repeated(const int arr[], int n) {
    int sum = 0;
    int *visited = (int *)calloc(n, sizeof(int));
    if (visited == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        if (visited[i] == 1) {
            continue;
        }

        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
                visited[j] = 1;
            }
        }

        if (count == 1) {
            sum += arr[i];
        }
    }

    free(visited);
    return sum;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    int result = sum_non_repeated(arr, n);

    if (result == -1) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Sum of non-repeated elements: %d\n", result);

    return EXIT_SUCCESS;
}