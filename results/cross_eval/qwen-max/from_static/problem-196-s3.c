#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} tuple_t;

void free_tuple(tuple_t *t) {
    free(t->data);
    t->data = NULL;
    t->len = 0;
}

tuple_t *remove_tuples(tuple_t *arr, size_t *size, size_t k) {
    if (arr == NULL || size == NULL) return NULL;
    size_t new_size = 0;
    for (size_t i = 0; i < *size; ++i) {
        if (arr[i].len != k) {
            arr[new_size] = arr[i];
            new_size++;
        } else {
            free_tuple(&arr[i]);
        }
    }
    *size = new_size;
    return arr;
}

int main() {
    size_t size = 5;
    tuple_t *arr = (tuple_t *)malloc(size * sizeof(tuple_t));
    if (arr == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6, 7};
    int data3[] = {8, 9};
    int data4[] = {10, 11, 12, 13, 14};
    int data5[] = {15};

    arr[0] = (tuple_t){ .data = data1, .len = 3 };
    arr[1] = (tuple_t){ .data = data2, .len = 4 };
    arr[2] = (tuple_t){ .data = data3, .len = 2 };
    arr[3] = (tuple_t){ .data = data4, .len = 5 };
    arr[4] = (tuple_t){ .data = data5, .len = 1 };

    size_t k = 4;
    arr = remove_tuples(arr, &size, k);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < arr[i].len; ++j) {
            printf("%d ", arr[i].data[j]);
        }
        printf("\n");
    }

    for (size_t i = 0; i < 5; ++i) {
        free_tuple(&arr[i]);
    }
    free(arr);

    return 0;
}