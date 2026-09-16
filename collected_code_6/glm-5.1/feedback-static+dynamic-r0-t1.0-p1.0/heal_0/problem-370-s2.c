#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    float value;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    float val_a = ((const Tuple *)a)->value;
    float val_b = ((const Tuple *)b)->value;
    if (val_a < val_b) {
        return -1;
    }
    if (val_a > val_b) {
        return 1;
    }
    return 0;
}

int main(void) {
    size_t n = 5;
    Tuple *arr = malloc(n * sizeof(Tuple));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    arr[0].id = 1; arr[0].value = 3.14f;
    arr[1].id = 2; arr[1].value = 1.41f;
    arr[2].id = 3; arr[2].value = 2.71f;
    arr[3].id = 4; arr[3].value = 1.61f;
    arr[4].id = 5; arr[4].value = 0.57f;

    qsort(arr, n, sizeof(Tuple), compare_tuples);

    for (size_t i = 0; i < n; i++) {
        printf("%d: %f\n", arr[i].id, arr[i].value);
    }

    free(arr);
    return EXIT_SUCCESS;
}