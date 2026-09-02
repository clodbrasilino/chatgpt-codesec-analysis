#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *arr;
    size_t len;
} Tuple;

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int isSubset(const int *a, size_t aLen, const int *b, size_t bLen) {
    for (size_t i = 0; i < aLen; i++) {
        int found = 0;
        for (size_t j = 0; j < bLen; j++) {
            if (a[i] == b[j]) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

Tuple* findIntersection(Tuple *tuples, size_t count) {
    qsort(tuples[0].arr, tuples[0].len, sizeof(int), compare);
    for (size_t i = 1; i < count; i++) {
        qsort(tuples[i].arr, tuples[i].len, sizeof(int), compare);
        tuples[0].arr = realloc(tuples[0].arr, sizeof(int) * tuples[0].len);
        if (tuples[0].arr == NULL) exit(EXIT_FAILURE);
        int *intersection = malloc(sizeof(int) * tuples[0].len);
        if (intersection == NULL) exit(EXIT_FAILURE);
        size_t k = 0;
        for (size_t j = 0; j < tuples[0].len; j++) {
            if (isSubset(&tuples[0].arr[j], 1, tuples[i].arr, tuples[i].len)) {
                intersection[k++] = tuples[0].arr[j];
            }
        }
        free(tuples[0].arr);
        tuples[0].arr = realloc(intersection, k * sizeof(int));
        if (tuples[0].arr == NULL) exit(EXIT_FAILURE);
        tuples[0].len = k;
    }
    return &tuples[0];
}

int main() {
    Tuple tuple1 = { .arr = (int[]){3, 1, 2}, .len = 3 };
    Tuple tuple2 = { .arr = (int[]){2, 3, 4}, .len = 3 };
    Tuple tuple3 = { .arr = (int[]){1, 2, 3, 4, 5}, .len = 5 };
    Tuple *tuples[] = { &tuple1, &tuple2, &tuple3 };
    size_t count = 3;

    Tuple *result = findIntersection(tuples, count);

    for (size_t i = 0; i < result->len; i++) {
        printf("%d ", result->arr[i]);
    }

    free(result->arr);
    return 0;
}