#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;
 /* Possible weaknesses found:
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got <no output>
  *  test case 0 failed: expected '[(2,), (9,), (2,), (2,)]', got <no output>
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got <no output>
  */

TupleList* trim_tuples(const TupleList *input_list, size_t k) {
    if (!input_list || !input_list->tuples) {
        return NULL;
    }

    TupleList *output_list = (TupleList *)malloc(sizeof(TupleList));
    if (!output_list) {
        return NULL;
    }

    output_list->count = input_list->count;
    output_list->tuples = (Tuple *)malloc(output_list->count * sizeof(Tuple));
    if (!output_list->tuples) {
        free(output_list);
        return NULL;
    }

    for (size_t i = 0; i < input_list->count; ++i) {
        size_t original_size = input_list->tuples[i].size;
        size_t new_size = (original_size > k) ? (original_size - k) : 0;

        output_list->tuples[i].size = new_size;
        
        if (new_size > 0) {
            output_list->tuples[i].elements = (int *)malloc(new_size * sizeof(int));
            if (!output_list->tuples[i].elements) {
                for (size_t j = 0; j < i; ++j) {
                    free(output_list->tuples[j].elements);
                }
                free(output_list->tuples);
                free(output_list);
                return NULL;
            }
            for (size_t j = 0; j < new_size; ++j) {
                output_list->tuples[i].elements[j] = input_list->tuples[i].elements[j];
            }
        } else {
            output_list->tuples[i].elements = NULL;
        }
    }

    return output_list;
}

void free_tuple_list(TupleList *list) {
    if (!list) {
        return;
    }
    if (list->tuples) {
        for (size_t i = 0; i < list->count; ++i) {
            free(list->tuples[i].elements);
        }
        free(list->tuples);
    }
    free(list);
}

int main(void) {
    TupleList input_list;
    input_list.count = 2;
    input_list.tuples = (Tuple *)malloc(input_list.count * sizeof(Tuple));
    if (!input_list.tuples) {
        return 1;
    }

    input_list.tuples[0].size = 5;
    input_list.tuples[0].elements = (int *)malloc(5 * sizeof(int));
    if (!input_list.tuples[0].elements) {
        free(input_list.tuples);
        return 1;
    }
    for (int i = 0; i < 5; ++i) input_list.tuples[0].elements[i] = i + 1;

    input_list.tuples[1].size = 3;
    input_list.tuples[1].elements = (int *)malloc(3 * sizeof(int));
    if (!input_list.tuples[1].elements) {
        free(input_list.tuples[0].elements);
        free(input_list.tuples);
        return 1;
    }
    for (int i = 0; i < 3; ++i) input_list.tuples[1].elements[i] = (i + 1) * 10;

    TupleList *trimmed_list = trim_tuples(&input_list, 2);
    if (!trimmed_list) {
        free_tuple_list(&input_list);
        return 1;
    }

    for (size_t i = 0; i < trimmed_list->count; ++i) {
        for (size_t j = 0; j < trimmed_list->tuples[i].size; ++j) {
            printf("%d ", trimmed_list->tuples[i].elements[j]);
        }
        printf("\n");
    }

    free_tuple_list(&input_list);
    free_tuple_list(trimmed_list);

    return 0;
}