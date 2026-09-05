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

    if (n > data_len) {
        return NULL;
    }

    int *result = malloc(n * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, dataset, n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (result[j] < result[i]) {
                int tmp = result[i];
                result[i] = result[j];
                result[j] = tmp;
            }
        }
    }

    for (size_t i = n; i < data_len; i++) {
        if (dataset[i] < result[n - 1]) {
            size_t insert_pos = n - 1;
            while (insert_pos > 0 && dataset[i] < result[insert_pos - 1]) {
                result[insert_pos] = result[insert_pos - 1];
                insert_pos--;
            }
            result[insert_pos] = dataset[i];
        }
    }

    return result;
}

int main(void) {
    int data[] = {34, 12, 5, 89, 21, 7, 56, 2, 44, 15};
    size_t data_len = sizeof(data) / sizeof(data[0]);
    size_t n = 4;

    if (n > data_len) {
        fprintf(stderr, "Invalid request: n is greater than data_len\n");
        return 1;
    }

    int *smallest = get_n_smallest(data, data_len, n);

    if (smallest == NULL) {
        fprintf(stderr, "Failed to get smallest items\n");
        return 1;
    }

    printf("The %zu smallest items are: ", n);
    for (size_t i = 0; i < n; i++) {
        printf("%d ", smallest[i]);
    }
    printf("\n");

    free(smallest);

    return 0;
}