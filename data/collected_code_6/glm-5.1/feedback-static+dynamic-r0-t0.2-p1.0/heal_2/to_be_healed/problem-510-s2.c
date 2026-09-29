#include <stdio.h>
#include <stdlib.h>

int count_subsequences(const int arr[], int n, int k) {
    if (k <= 1) {
        return 0;
    }
    int result = 0;
    long long product = 1;
    int left = 0;
    for (int right = 0; right < n; right++) {
        product *= arr[right];
        while (product >= k && left <= right) {
            product /= arr[left];
            left++;
        }
        result += right - left + 1;
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s k element1 element2 ...\n", argv[0]);
        return 1;
    }
    char *endptr;
    long k_long = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || k_long < 0) {
        fprintf(stderr, "Invalid k value\n");
        return 1;
    }
    int k = (int)k_long;
    int n = argc - 2;
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        long val = strtol(argv[i + 2], &endptr, 10);
        if (*endptr != '\0' || val < 0) {
            fprintf(stderr, "Invalid array element\n");
            free(arr);
            return 1;
        }
        arr[i] = (int)val;
    }
    int count = count_subsequences(arr, n, k);
    printf("%d\n", count);
    free(arr);
    return 0;
}