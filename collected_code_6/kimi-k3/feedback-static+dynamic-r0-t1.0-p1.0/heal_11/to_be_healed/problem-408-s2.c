#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
    int first;
    int second;
} Pair;

static int compare_pairs(const void *a, const void *b)
{
    const Pair *pa = (const Pair *)a;
    const Pair *pb = (const Pair *)b;

    if (pa->first != pb->first) {
        return (pa->first > pb->first) - (pa->first < pb->first);
    }
    return (pa->second > pb->second) - (pa->second < pb->second);
}

Pair *find_k_pairs(const int *arr1, size_t size1, const int *arr2, size_t size2, size_t k, size_t *result_size)
{
    Pair *all_pairs = NULL;
    Pair *result = NULL;
    size_t total_pairs;
    size_t i;
    size_t j;
    size_t idx;
    size_t result_bytes;

    if (arr1 == NULL || arr2 == NULL || result_size == NULL || size1 == 0 || size2 == 0 || k == 0) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    if (size1 > SIZE_MAX / size2) {
        *result_size = 0;
        return NULL;
    }
    total_pairs = size1 * size2;

    if (total_pairs > SIZE_MAX / sizeof(Pair)) {
        *result_size = 0;
        return NULL;
    }

    if (k > total_pairs) {
        k = total_pairs;
    }

    all_pairs = (Pair *)malloc(total_pairs * sizeof(Pair));
    if (all_pairs == NULL) {
        *result_size = 0;
        return NULL;
    }

    idx = 0;
    for (i = 0; i < size1; i++) {
        for (j = 0; j < size2; j++) {
            all_pairs[idx].first = arr1[i];
            all_pairs[idx].second = arr2[j];
            idx++;
        }
    }

    qsort(all_pairs, total_pairs, sizeof(Pair), compare_pairs);

    if (k > SIZE_MAX / sizeof(Pair)) {
        free(all_pairs);
        *result_size = 0;
        return NULL;
    }

    result_bytes = k * sizeof(Pair);

    result = (Pair *)malloc(result_bytes);
    if (result == NULL) {
        free(all_pairs);
        *result_size = 0;
        return NULL;
    }

    if (result_bytes > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, all_pairs, result_bytes);
    }

    free(all_pairs);

    *result_size = k;
    return result;
}

int main(void)
{
    int arr1[] = {1, 7, 11};
    int arr2[] = {2, 4, 6};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t k = 3;
    size_t result_size = 0;
    Pair *pairs = NULL;
    size_t i;

    pairs = find_k_pairs(arr1, size1, arr2, size2, k, &result_size);

    if (pairs == NULL) {
        fprintf(stderr, "Error: Failed to find pairs\n");
        return EXIT_FAILURE;
    }

    printf("Found %zu pairs:\n", result_size);
    for (i = 0; i < result_size; i++) {
        printf("(%d, %d)\n", pairs[i].first, pairs[i].second);
    }

    free(pairs);
    return EXIT_SUCCESS;
}