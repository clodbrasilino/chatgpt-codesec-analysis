#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

int *find_union(Tuple *tuples, size_t num_tuples, size_t *union_size) {
    size_t capacity = 16;
    int *union_arr = (int *)malloc(capacity * sizeof(int));
    if (union_arr == NULL) {
        exit(EXIT_FAILURE);
    }

    *union_size = 0;

    for (size_t i = 0; i < num_tuples; i++) {
        for (size_t j = 0; j < tuples[i].size; j++) {
            int current = tuples[i].elements[j];
            int found = 0;

            for (size_t k = 0; k < *union_size; k++) {
                if (union_arr[k] == current) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                if (*union_size >= capacity) {
                    capacity *= 2;
                    int *temp = (int *)realloc(union_arr, capacity * sizeof(int));
                    if (temp == NULL) {
                        free(union_arr);
                        exit(EXIT_FAILURE);
                    }
                    union_arr = temp;
                }
                union_arr[*union_size] = current;
                (*union_size)++;
            }
        }
    }

    return union_arr;
}

int main() {
    int a[] = {1, 2, 3};
    int b[] = {3, 4, 5};
    int c[] = {5, 6, 1};

    Tuple tuples[] = {
        {a, sizeof(a) / sizeof(a[0])},
        {b, sizeof(b) / sizeof(b[0])},
        {c, sizeof(c) / sizeof(c[0])}
    };

    size_t union_size = 0;
    int *union_arr = find_union(tuples, 3, &union_size);

    for (size_t i = 0; i < union_size; i++) {
        printf("%d ", union_arr[i]);
    }
    printf("\n");

    free(union_arr);

    return 0;
}