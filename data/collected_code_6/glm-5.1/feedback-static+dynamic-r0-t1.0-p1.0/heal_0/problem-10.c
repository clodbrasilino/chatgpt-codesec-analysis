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

int *get_n_smallest(const int *dataset, size_t data_len, size_t n) {
    if (dataset == NULL || data_len == 0 || n == 0) {
        return NULL;
    }

    size_t target_n = n > data_len ? data_len : n;

    int *temp = malloc(data_len * sizeof(int));
    if (temp == NULL) {
        return NULL;
    }

    memcpy(temp, dataset, data_len * sizeof(int));

    qsort(temp, data_len, sizeof(int), cmp_int);

    int *result = malloc(target_n * sizeof(int));
    if (result == NULL) {
        free(temp);
        return NULL;
    }

    memcpy(result, temp, target_n * sizeof(int));

    free(temp);

    return result;
}

int main(void) {
    int data[] = {34, 12, 5, 89, 21, 7, 56, 2, 44, 15};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 4;

    int *smallest = get_n_smallest(data, data_len, n);

    if (smallest == NULL) {
        fprintf(stderr, "Failed to get smallest items\n");
        return 1;
    }

    size_t target_n = n > data_len ? data_len : n;

    printf("The %zu smallest items are: ", target_n);
    for (size_t i = 0; i < target_n; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");

    free(smallest);

    return 0;
}