#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int compare_tuples(const void *t1, const void *t2) {
    Tuple *tuple1 = (Tuple *)t1;
    Tuple *tuple2 = (Tuple *)t2;
    if (tuple1->a == tuple2->a && tuple1->b == tuple2->b) return 0;
    return 1;
}

void remove_matching_tuples(Tuple *tuple1, size_t n1, Tuple *tuple2, size_t n2, Tuple **result, size_t *result_size) {
    for (size_t i = 0; i < n1; ++i) {
        int found = 0;
        for (size_t j = 0; j < n2; ++j) {
            if (compare_tuples(&tuple1[i], &tuple2[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            (*result)[(*result_size)++] = tuple1[i];
        }
    }
}

int main() {
    Tuple tuple1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple tuple2[] = {{3, 4}, {7, 8}};
    size_t n1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t n2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t result_size = 0;
    Tuple *result = (Tuple *)malloc(n1 * sizeof(Tuple));
    if (result == NULL) {
        return 1;
    }
    remove_matching_tuples(tuple1, n1, tuple2, n2, &result, &result_size);
    for (size_t i = 0; i < result_size; ++i) {
        printf("(%d, %d)\n", result[i].a, result[i].b);
    }
    free(result);
    return 0;
}