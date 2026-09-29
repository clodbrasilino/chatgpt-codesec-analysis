#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple* tuples;
    size_t count;
} TupleList;

bool all_divisible_by_k(const Tuple* tuple, int k) {
    if (k == 0) {
        return false;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->elements[i] % k != 0) {
            return false;
        }
    }
    return true;
}

TupleList find_divisible_tuples(const TupleList* input, int k) {
    TupleList result;
    result.count = 0;
    result.tuples = NULL;

    if (input == NULL || input->count == 0 || k == 0) {
        return result;
    }

    result.tuples = (Tuple*)malloc(input->count * sizeof(Tuple));
    if (result.tuples == NULL) {
        return result;
    }

    for (size_t i = 0; i < input->count; i++) {
        if (all_divisible_by_k(&input->tuples[i], k)) {
            result.tuples[result.count].size = input->tuples[i].size;
            result.tuples[result.count].elements = (int*)malloc(input->tuples[i].size * sizeof(int));
            if (result.tuples[result.count].elements != NULL) {
                for (size_t j = 0; j < input->tuples[i].size; j++) {
                    result.tuples[result.count].elements[j] = input->tuples[i].elements[j];
                }
                result.count++;
            }
        }
    }

    if (result.count == 0) {
        free(result.tuples);
        result.tuples = NULL;
    } else if (result.count < input->count) {
        Tuple* resized = (Tuple*)realloc(result.tuples, result.count * sizeof(Tuple));
        if (resized != NULL) {
            result.tuples = resized;
        }
    }

    return result;
}

void free_tuple_list(TupleList* list) {
    if (list != NULL && list->tuples != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->tuples[i].elements);
        }
        free(list->tuples);
        list->tuples = NULL;
        list->count = 0;
    }
}

int main() {
    int k = 3;
    
    int t1_data[] = {3, 6, 9};
    int t2_data[] = {3, 4, 9};
    int t3_data[] = {12, 15};
    int t4_data[] = {1, 2, 3};

    Tuple tuples[] = {
        {t1_data, 3},
        {t2_data, 3},
        {t3_data, 2},
        {t4_data, 3}
    };

    TupleList input_list = {tuples, 4};

    TupleList result_list = find_divisible_tuples(&input_list, k);

    for (size_t i = 0; i < result_list.count; i++) {
        printf("(");
        for (size_t j = 0; j < result_list.tuples[i].size; j++) {
            printf("%d", result_list.tuples[i].elements[j]);
            if (j < result_list.tuples[i].size - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuple_list(&result_list);

    return 0;
}