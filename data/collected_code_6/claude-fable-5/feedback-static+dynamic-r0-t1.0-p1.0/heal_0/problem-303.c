#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 100000

static bool same_inversion_counts(const long long *arr, size_t n)
{
    unsigned long long count_type1 = 0;
    unsigned long long count_type2 = 0;
    size_t i;
    size_t j;

    for (i = 0; i + 1 < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                count_type1++;
            }
            if (arr[i] > 2 * arr[j]) {
                count_type2++;
            }
        }
    }

    return count_type1 == count_type2;
}

int main(void)
{
    size_t n = 0;
    size_t i;
    long long *arr = NULL;

    if (scanf("%zu", &n) != 1) {
        fprintf(stderr, "Error: failed to read array size\n");
        return EXIT_FAILURE;
    }

    if (n == 0 || n > MAX_N) {
        fprintf(stderr, "Error: array size must be between 1 and %d\n", MAX_N);
        return EXIT_FAILURE;
    }

    arr = malloc(n * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%lld", &arr[i]) != 1) {
            fprintf(stderr, "Error: failed to read element %zu\n", i);
            free(arr);
            return EXIT_FAILURE;
        }
        if (arr[i] > 1000000000LL || arr[i] < -1000000000LL) {
            fprintf(stderr, "Error: element %zu out of allowed range\n", i);
            free(arr);
            return EXIT_FAILURE;
        }
    }

    if (same_inversion_counts(arr, n)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    free(arr);
    return EXIT_SUCCESS;
}