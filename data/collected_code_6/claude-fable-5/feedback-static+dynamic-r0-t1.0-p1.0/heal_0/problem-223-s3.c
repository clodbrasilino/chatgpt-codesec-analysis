#include <stdio.h>
#include <stdlib.h>

static int firstOccurrence(const int *arr, int n, int target)
{
    int low = 0;
    int high = n - 1;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            result = mid;
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

int isMajorityElement(const int *arr, int n, int candidate)
{
    if (arr == NULL || n <= 0) {
        return 0;
    }

    int first = firstOccurrence(arr, n, candidate);
    if (first == -1) {
        return 0;
    }

    int lastPossible = first + n / 2;
    if (lastPossible < n && arr[lastPossible] == candidate) {
        return 1;
    }
    return 0;
}

int main(void)
{
    int n = 0;
    int candidate = 0;

    if (printf("Enter number of elements: ") < 0) {
        return EXIT_FAILURE;
    }
    if (scanf("%d", &n) != 1 || n <= 0 || n > 1000000) {
        fprintf(stderr, "Invalid array size\n");
        return EXIT_FAILURE;
    }

    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Enter %d sorted integers: ", n) < 0) {
        free(arr);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
        if (i > 0 && arr[i] < arr[i - 1]) {
            fprintf(stderr, "Array is not sorted\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    if (printf("Enter candidate element: ") < 0) {
        free(arr);
        return EXIT_FAILURE;
    }
    if (scanf("%d", &candidate) != 1) {
        fprintf(stderr, "Invalid input\n");
        free(arr);
        return EXIT_FAILURE;
    }

    if (isMajorityElement(arr, n, candidate)) {
        printf("%d is a majority element\n", candidate);
    } else {
        printf("%d is not a majority element\n", candidate);
    }

    free(arr);
    return EXIT_SUCCESS;
}