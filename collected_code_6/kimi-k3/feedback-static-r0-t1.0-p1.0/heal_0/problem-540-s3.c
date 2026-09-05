#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int findFrequencyDifference(int arr[], int n) {
    if (n <= 0) {
        return -1;
    }

    qsort(arr, n, sizeof(int), compare);

    int maxFreq = 1;
    int minFreq = n;
    int currentFreq = 1;

    for (int i = 1; i < n; i++) {
        if (arr[i] == arr[i - 1]) {
            currentFreq++;
        } else {
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
            }
            if (currentFreq < minFreq) {
                minFreq = currentFreq;
            }
            currentFreq = 1;
        }
    }

    if (currentFreq > maxFreq) {
        maxFreq = currentFreq;
    }
    if (currentFreq < minFreq) {
        minFreq = currentFreq;
    }

    return maxFreq - minFreq;
}

int main() {
    int n;

    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    int result = findFrequencyDifference(arr, n);
    printf("%d\n", result);

    free(arr);
    return EXIT_SUCCESS;
}