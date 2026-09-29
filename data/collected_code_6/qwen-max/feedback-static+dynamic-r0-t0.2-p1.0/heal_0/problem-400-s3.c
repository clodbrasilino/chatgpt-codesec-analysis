#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple tuple;
    int count;
} TupleCount;

int compare_tuples(const void *a, const void *b) {
    return (memcmp(a, b, sizeof(Tuple)));
}

int main() {
    Tuple list[] = {{1, 2}, {3, 4}, {1, 2}, {5, 6}, {3, 4}, {1, 2}};
    int n = sizeof(list) / sizeof(list[0]);
    qsort(list, n, sizeof(Tuple), compare_tuples);

    TupleCount *result = (TupleCount *)malloc(n * sizeof(TupleCount));
    if (result == NULL) {
        return 1;
    }

    int unique_count = 0;
    result[unique_count].tuple = list[0];
    result[unique_count].count = 1;

    for (int i = 1; i < n; i++) {
        if (compare_tuples(&list[i], &list[i - 1]) != 0) {
            unique_count++;
            result[unique_count].tuple = list[i];
            result[unique_count].count = 1;
        } else {
            result[unique_count].count++;
        }
    }

    for (int i = 0; i <= unique_count; i++) {
        printf("Tuple: (%d, %d) Count: %d\n", result[i].tuple.a, result[i].tuple.b, result[i].count);
    }

    free(result);
    return 0;
}