#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int compare_tuples(const void *t1, const void *t2) {
    Tuple *tuple1 = (Tuple *)t1;
    Tuple *tuple2 = (Tuple *)t2;
    if (tuple1->a == tuple2->a && tuple1->b == tuple2->b) {
        return 0;
    }
    return 1;
}

void remove_matching_tuples(Tuple *tuple1, Tuple *tuple2, int n1, int n2, Tuple **result, int *result_size) {
    *result = malloc(n1 * sizeof(Tuple));
    if (*result == NULL) {
        exit(EXIT_FAILURE);
    }
    *result_size = 0;
    for (int i = 0; i < n1; ++i) {
        int found = 0;
        for (int j = 0; j < n2; ++j) {
            if (compare_tuples(&tuple1[i], &tuple2[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            (*result)[*result_size] = tuple1[i];
            (*result_size)++;
        }
    }
}

int main() {
    Tuple tuple1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple tuple2[] = {{3, 4}, {7, 8}};
    int n1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int n2 = sizeof(tuple2) / sizeof(tuple2[0]);

    Tuple *result;
    int result_size;
    remove_matching_tuples(tuple1, tuple2, n1, n2, &result, &result_size);

    for (int i = 0; i < result_size; ++i) {
        printf("(%d, %d)\n", result[i].a, result[i].b);
    }

    free(result);
    return 0;
}