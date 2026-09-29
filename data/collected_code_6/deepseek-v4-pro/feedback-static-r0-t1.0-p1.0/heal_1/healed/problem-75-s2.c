#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    int size;
} Tuple;

Tuple* create_tuple(const int *elements, int size) {
    if (elements == NULL || size <= 0) {
        return NULL;
    }
    
    Tuple *tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    
    tuple->elements = (int*)malloc(size * sizeof(int));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }
    
    for (int i = 0; i < size; i++) {
        tuple->elements[i] = elements[i];
    }
    
    tuple->size = size;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->elements);
        free(tuple);
    }
}

void free_tuple_array(Tuple **tuples, int count) {
    if (tuples == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free_tuple(tuples[i]);
    }
    free(tuples);
}

bool is_tuple_divisible_by_k(Tuple *tuple, int k) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size <= 0 || k == 0) {
        return false;
    }
    for (int i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] % k != 0) {
            return false;
        }
    }
    return true;
}

Tuple** find_divisible_tuples(Tuple **tuples, int tuple_count, int k, int *result_count) {
    if (result_count == NULL) {
        return NULL;
    }
    
    if (tuples == NULL || tuple_count <= 0 || k == 0) {
        *result_count = 0;
        return NULL;
    }

    Tuple **result = (Tuple**)malloc(tuple_count * sizeof(Tuple*));
    if (result == NULL) {
        *result_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < tuple_count; i++) {
        if (is_tuple_divisible_by_k(tuples[i], k)) {
            Tuple *copy = create_tuple(tuples[i]->elements, tuples[i]->size);
            if (copy == NULL) {
                for (int j = 0; j < count; j++) {
                    free_tuple(result[j]);
                }
                free(result);
                *result_count = 0;
                return NULL;
            }
            result[count] = copy;
            count++;
        }
    }

    if (count == 0) {
        free(result);
        *result_count = 0;
        return NULL;
    }

    Tuple **final_result = (Tuple**)realloc(result, count * sizeof(Tuple*));
    if (final_result == NULL) {
        for (int j = 0; j < count; j++) {
            free_tuple(result[j]);
        }
        free(result);
        *result_count = 0;
        return NULL;
    }

    *result_count = count;
    return final_result;
}

void print_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    printf("(");
    for (int i = 0; i < tuple->size; i++) {
        printf("%d", tuple->elements[i]);
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")");
}

int main(void) {
    int tuple1_data[] = {2, 4, 6};
    int tuple2_data[] = {3, 6, 9};
    int tuple3_data[] = {12, 18, 24};
    int tuple4_data[] = {5, 10, 15};

    Tuple *tuple1 = create_tuple(tuple1_data, 3);
    Tuple *tuple2 = create_tuple(tuple2_data, 3);
    Tuple *tuple3 = create_tuple(tuple3_data, 3);
    Tuple *tuple4 = create_tuple(tuple4_data, 3);

    if (tuple1 == NULL || tuple2 == NULL || tuple3 == NULL || tuple4 == NULL) {
        free_tuple(tuple1);
        free_tuple(tuple2);
        free_tuple(tuple3);
        free_tuple(tuple4);
        return 1;
    }

    Tuple *tuples[] = {tuple1, tuple2, tuple3, tuple4};
    int tuple_count = 4;
    int k = 3;
    int result_count = 0;

    Tuple **divisible_tuples = find_divisible_tuples(tuples, tuple_count, k, &result_count);

    if (divisible_tuples == NULL) {
        printf("No tuples found or error occurred.\n");
    } else {
        printf("Tuples with all elements divisible by %d:\n", k);
        for (int i = 0; i < result_count; i++) {
            print_tuple(divisible_tuples[i]);
            printf("\n");
        }
    }

    free_tuple_array(divisible_tuples, result_count);
    free_tuple(tuple1);
    free_tuple(tuple2);
    free_tuple(tuple3);
    free_tuple(tuple4);

    return 0;
}