#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;
 /* Possible weaknesses found:
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got <no output>
  *  test case 0 failed: expected '[(2,), (9,), (2,), (2,)]', got <no output>
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got <no output>
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
    if (!list) return;
    if (list->tuples) {
        for (size_t i = 0; i < list->count; ++i) {
            free(list->tuples[i].elements);
        }
        free(list->tuples);
    }
    free(list);
}

void print_tuple_list(const TupleList *list) {
    if (!list) return;
    printf("[");
    for (size_t i = 0; i < list->count; ++i) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        if (list->tuples[i].size == 1) {
            printf(",");
        }
        printf(")");
        if (i < list->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    TupleList input_list;
    input_list.count = 4;
    input_list.tuples = (Tuple *)malloc(input_list.count * sizeof(Tuple));
    
    int t1[] = {3, 2, 1, 0};
    int t2[] = {4, 9, 2, 0};
    int t3[] = {1, 2, 3, 0};
    int t4[] = {8, 2, 1, 0};
    int *t_arr[] = {t1, t2, t3, t4};
    
    const size_t sizes[] = {4, 4, 4, 4};
    
    for (int i = 0; i < 4; i++) {
        input_list.tuples[i].size = sizes[i];
        input_list.tuples[i].elements = (int *)malloc(sizes[i] * sizeof(int));
        for (size_t j = 0; j < sizes[i]; j++) {
            input_list.tuples[i].elements[j] = t_arr[i][j];
        }
    }

    TupleList *trimmed_list = trim_tuples(&input_list, 1);
    if (trimmed_list) {
        print_tuple_list(trimmed_list);
        free_tuple_list(trimmed_list);
    }
    
    if (input_list.tuples) {
        for (size_t i = 0; i < input_list.count; ++i) {
            free(input_list.tuples[i].elements);
        }
        free(input_list.tuples);
    }
    
    return 0;
}