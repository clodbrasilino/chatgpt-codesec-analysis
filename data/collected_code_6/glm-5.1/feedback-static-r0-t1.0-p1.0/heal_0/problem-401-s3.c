#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int size;
} NestedTuple;

NestedTuple create_nested_tuple(int tuple_count, int tuple_size) {
    NestedTuple nt;
    nt.size = tuple_count;
    nt.tuples = (Tuple *)malloc(tuple_count * sizeof(Tuple));
    for (int i = 0; i < tuple_count; i++) {
        nt.tuples[i].size = tuple_size;
        nt.tuples[i].elements = (int *)malloc(tuple_size * sizeof(int));
    }
    return nt;
}

void free_nested_tuple(NestedTuple *nt) {
    for (int i = 0; i < nt->size; i++) {
        free(nt->tuples[i].elements);
    }
    free(nt->tuples);
    nt->tuples = NULL;
    nt->size = 0;
}

NestedTuple add_nested_tuples(NestedTuple a, NestedTuple b) {
    int min_tuple_size = a.size < b.size ? a.size : b.size;
    int result_size = a.size > b.size ? a.size : b.size;
    NestedTuple result = create_nested_tuple(result_size, 0);

    for (int i = 0; i < min_tuple_size; i++) {
        int min_elem_size = a.tuples[i].size < b.tuples[i].size ? a.tuples[i].size : b.tuples[i].size;
        int res_elem_size = a.tuples[i].size > b.tuples[i].size ? a.tuples[i].size : b.tuples[i].size;
        result.tuples[i].size = res_elem_size;
        free(result.tuples[i].elements);
        result.tuples[i].elements = (int *)malloc(res_elem_size * sizeof(int));
        for (int j = 0; j < min_elem_size; j++) {
            result.tuples[i].elements[j] = a.tuples[i].elements[j] + b.tuples[i].elements[j];
        }
        for (int j = min_elem_size; j < a.tuples[i].size; j++) {
            result.tuples[i].elements[j] = a.tuples[i].elements[j];
        }
        for (int j = min_elem_size; j < b.tuples[i].size; j++) {
            result.tuples[i].elements[j] = b.tuples[i].elements[j];
        }
    }

    for (int i = min_tuple_size; i < a.size; i++) {
        result.tuples[i].size = a.tuples[i].size;
        free(result.tuples[i].elements);
        result.tuples[i].elements = (int *)malloc(a.tuples[i].size * sizeof(int));
        for (int j = 0; j < a.tuples[i].size; j++) {
            result.tuples[i].elements[j] = a.tuples[i].elements[j];
        }
    }

    for (int i = min_tuple_size; i < b.size; i++) {
        result.tuples[i].size = b.tuples[i].size;
        free(result.tuples[i].elements);
        result.tuples[i].elements = (int *)malloc(b.tuples[i].size * sizeof(int));
        for (int j = 0; j < b.tuples[i].size; j++) {
            result.tuples[i].elements[j] = b.tuples[i].elements[j];
        }
    }

    return result;
}

int main() {
    NestedTuple a = create_nested_tuple(2, 2);
    a.tuples[0].elements[0] = 1;
    a.tuples[0].elements[1] = 2;
    a.tuples[1].elements[0] = 3;
    a.tuples[1].elements[1] = 4;

    NestedTuple b = create_nested_tuple(2, 2);
    b.tuples[0].elements[0] = 5;
    b.tuples[0].elements[1] = 6;
    b.tuples[1].elements[0] = 7;
    b.tuples[1].elements[1] = 8;

    NestedTuple result = add_nested_tuples(a, b);

    for (int i = 0; i < result.size; i++) {
        printf("(");
        for (int j = 0; j < result.tuples[i].size; j++) {
            printf("%d", result.tuples[i].elements[j]);
            if (j < result.tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_nested_tuple(&a);
    free_nested_tuple(&b);
    free_nested_tuple(&result);

    return 0;
}