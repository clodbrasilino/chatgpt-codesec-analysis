#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

void sort_int_array(int *arr, size_t count) {
    if (count <= 1) return;
    size_t i, j;
    int temp;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int tuple_equal(Tuple a, Tuple b) {
    if (a.count != b.count) {
        return 0;
    }
    for (size_t i = 0; i < a.count; i++) {
        if (a.elements[i] != b.elements[i]) {
            return 0;
        }
    }
    return 1;
}

TupleList find_tuple_intersection(TupleList list) {
    TupleList result;
    result.tuples = NULL;
    result.count = 0;

    if (list.count == 0) {
        return result;
    }

    for (size_t i = 0; i < list.count; i++) {
        sort_int_array(list.tuples[i].elements, list.tuples[i].count);
    }

    int *is_unique = (int *)malloc(list.count * sizeof(int));
    if (is_unique == NULL) {
        return result;
    }

    for (size_t i = 0; i < list.count; i++) {
        is_unique[i] = 1;
    }

    for (size_t i = 0; i < list.count; i++) {
        if (!is_unique[i]) {
            continue;
        }
        for (size_t j = i + 1; j < list.count; j++) {
            if (!is_unique[j]) {
                continue;
            }
            if (tuple_equal(list.tuples[i], list.tuples[j])) {
                is_unique[j] = 0;
            }
        }
    }

    size_t unique_count = 0;
    for (size_t i = 0; i < list.count; i++) {
        if (is_unique[i]) {
            unique_count++;
        }
    }

    if (unique_count == 0) {
        free(is_unique);
        return result;
    }

    result.tuples = (Tuple *)malloc(unique_count * sizeof(Tuple));
    if (result.tuples == NULL) {
        free(is_unique);
        return result;
    }

    size_t res_idx = 0;
    for (size_t i = 0; i < list.count; i++) {
        if (is_unique[i]) {
            result.tuples[res_idx].count = list.tuples[i].count;
            if (list.tuples[i].count > 0) {
                size_t element_size = list.tuples[i].count * sizeof(int);
                result.tuples[res_idx].elements = (int *)malloc(element_size);
                if (result.tuples[res_idx].elements != NULL) {
                    memcpy(result.tuples[res_idx].elements, list.tuples[i].elements, element_size);
                } else {
                    result.tuples[res_idx].elements = NULL;
                    result.tuples[res_idx].count = 0;
                }
            } else {
                result.tuples[res_idx].elements = NULL;
            }
            res_idx++;
        }
    }

    result.count = res_idx;
    free(is_unique);
    return result;
}

void free_tuple_list(TupleList list) {
    for (size_t i = 0; i < list.count; i++) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);
}

int main() {
    int e1[] = {3, 1, 2};
    int e2[] = {1, 2, 3};
    int e3[] = {4, 5};
    int e4[] = {5, 4};
    int e5[] = {1, 2, 3};

    Tuple t_arr[5];
    t_arr[0].elements = e1; t_arr[0].count = 3;
    t_arr[1].elements = e2; t_arr[1].count = 3;
    t_arr[2].elements = e3; t_arr[2].count = 2;
    t_arr[3].elements = e4; t_arr[3].count = 2;
    t_arr[4].elements = e5; t_arr[4].count = 3;

    TupleList input;
    input.tuples = t_arr;
    input.count = 5;

    TupleList output = find_tuple_intersection(input);

    for (size_t i = 0; i < output.count; i++) {
        printf("(");
        for (size_t j = 0; j < output.tuples[i].count; j++) {
            printf("%d", output.tuples[i].elements[j]);
            if (j < output.tuples[i].count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuple_list(output);

    return 0;
}