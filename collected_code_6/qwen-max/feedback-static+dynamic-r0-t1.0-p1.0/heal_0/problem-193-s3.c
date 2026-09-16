#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

Tuple* create_tuple(int arr[], int n) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    t->data = (int *)malloc(n * sizeof(int));
    t->size = n;
    for (int i = 0; i < n; ++i) {
        t->data[i] = arr[i];
    }
    return t;
}

void free_tuple(Tuple *t) {
    free(t->data);
    free(t);
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

Tuple* remove_duplicates(Tuple *t) {
    qsort(t->data, t->size, sizeof(int), compare);

    int *new_data = (int *)malloc(t->size * sizeof(int));
    if (new_data == NULL) {
        free(t->data);
        free(t);
        exit(EXIT_FAILURE);
    }

    int new_size = 1;
    new_data[0] = t->data[0];

    for (int i = 1; i < t->size; ++i) {
        if (t->data[i] != t->data[i - 1]) {
            new_data[new_size++] = t->data[i];
        }
    }

    free(t->data);
    t->data = new_data;
    t->size = new_size;

    return t;
}

int main() {
    int arr[] = {4, 2, 7, 2, 4, 8, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    Tuple *t = create_tuple(arr, n);

    t = remove_duplicates(t);

    for (int i = 0; i < t->size; ++i) {
        printf("%d ", t->data[i]);
    }
    printf("\n");

    free_tuple(t);

    return 0;
}