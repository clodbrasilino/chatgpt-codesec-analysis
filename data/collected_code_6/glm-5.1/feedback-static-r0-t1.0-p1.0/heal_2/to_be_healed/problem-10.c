#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int *get_n_smallest(const int *dataset, size_t data_len, size_t n, size_t *out_len) {
    if (dataset == NULL || data_len == 0 || n == 0 || out_len == NULL) {
        return NULL;
    }

    size_t target_n = n > data_len ? data_len : n;

    int *temp = malloc(data_len * sizeof(int));
    if (temp == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    if (data_len > SIZE_MAX / sizeof(int) || memcpy(temp, dataset, data_len * sizeof(int)) == NULL) {
        free(temp);
        return NULL;
    }

    qsort(temp, data_len, sizeof(int), cmp_int);

    int *result = malloc(target_n * sizeof(int));
    if (result == NULL) {
        free(temp);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    if (target_n > SIZE_MAX / sizeof(int) || memcpy(result, temp, target_n * sizeof(int)) == NULL) {
        free(temp);
        free(result);
        return NULL;
    }

    free(temp);
    *out_len = target_n;
    return result;
}

int main(void) {
    int data[] = {34, 12, 5, 89, 21, 7, 56, 2, 44, 15};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 4;
    size_t target_n = 0;

    int *smallest = get_n_smallest(data, data_len, n, &target_n);

    if (smallest == NULL) {
        fprintf(stderr, "Failed to get smallest items\n");
        return 1;
    }

    printf("The %zu smallest items are: ", target_n);
    for (size_t i = 0; i < target_n; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");

    free(smallest);

    return 0;
}