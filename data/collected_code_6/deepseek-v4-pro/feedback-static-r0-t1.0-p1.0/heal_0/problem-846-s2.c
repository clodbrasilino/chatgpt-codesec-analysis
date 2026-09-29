#include <stdio.h>
#include <stdlib.h>

int findMinimumPlatforms(int arr[], int dep[], int n) {
    int i = 0, j = 0, platforms_needed = 0, max_platforms = 0;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            platforms_needed++;
            i++;
            if (platforms_needed > max_platforms) {
                max_platforms = platforms_needed;
            }
        } else {
            platforms_needed--;
            j++;
        }
    }

    return max_platforms;
}

int compareIntegers(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int n;
    int *arr = NULL;
    int *dep = NULL;
    int result;

    printf("Enter total number of trains: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    arr = (int *)malloc((size_t)n * sizeof(int));
    dep = (int *)malloc((size_t)n * sizeof(int));

    if (arr == NULL || dep == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(arr);
        free(dep);
        return EXIT_FAILURE;
    }

    printf("Enter arrival times: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            free(dep);
            return EXIT_FAILURE;
        }
    }

    printf("Enter departure times: ");
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &dep[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            free(dep);
            return EXIT_FAILURE;
        }
    }

    qsort(arr, (size_t)n, sizeof(int), compareIntegers);
    qsort(dep, (size_t)n, sizeof(int), compareIntegers);

    result = findMinimumPlatforms(arr, dep, n);

    printf("Minimum number of platforms required: %d\n", result);

    free(arr);
    free(dep);

    return EXIT_SUCCESS;
}