#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int cmp_int(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int *get_n_smallest(const int *dataset, size_t data_len, size_t n, size_t *out_len) {
    if (dataset == NULL || data_len == 0 || n == 0) {
        return NULL;
    }

    size_t target_n = n > data_len ? data_len : n;

    if (data_len > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    int *temp = malloc(data_len * sizeof(int));
    if (temp == NULL) {
        return NULL;
    }

    if (memcpy_s(temp, data_len * sizeof(int), dataset, data_len * sizeof(int)) != 0) {
        free(temp);
        return NULL;
    }

    qsort(temp, data_len, sizeof(int), cmp_int);

    if (target_n > SIZE_MAX / sizeof(int)) {
        free(temp);
        return NULL;
    }

    int *result = malloc(target_n * sizeof(int));
    if (result == NULL) {
        free(temp);
        return NULL;
    }

    if (memcpy_s(result, target_n * sizeof(int), temp, target_n * sizeof(int)) != 0) {
        free(temp);
        free(result);
        return NULL;
    }

    free(temp);

    if (out_len) {
        *out_len = target_n;
    }

    return result;
}

int main(void) {
    int data[] = {34, 12, 5, 89, 21, 7, 56, 2, 44, 15};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 0;

    if (scanf("%zu", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid request for 0 or invalid items\n");
        return 1;
    }

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