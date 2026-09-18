#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int *values;
    size_t num_values;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

TupleList* create_tuple_list(size_t initial_capacity) {
    if (initial_capacity == 0) {
        return NULL;
    }
    TupleList *list = malloc(sizeof(TupleList));
    if (!list) {
        return NULL;
    }
    list->tuples = malloc(initial_capacity * sizeof(Tuple));
    if (!list->tuples) {
        free(list);
        return NULL;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return list;
}

void free_tuple_list(TupleList *list) {
    if (!list) {
        return;
    }
    for (size_t i = 0; i < list->count; ++i) {
        free(list->tuples[i].values);
    }
    free(list->tuples);
    free(list);
}

int add_tuple(TupleList *list, int id, const int *values, size_t num_values) {
    if (!list || (!values && num_values > 0)) {
        return -1;
    }
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_tuples = realloc(list->tuples, new_capacity * sizeof(Tuple));
        if (!new_tuples) {
            return -1;
        }
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }
    
    Tuple *t = &list->tuples[list->count];
    t->id = id;
    t->num_values = num_values;
    if (num_values > 0) {
        t->values = malloc(num_values * sizeof(int));
        if (!t->values) {
            return -1;
        }
        memcpy(t->values, values, num_values * sizeof(int));
    } else {
        t->values = NULL;
    }
    list->count++;
    return 0;
}

TupleList* join_tuples(const TupleList *input) {
    if (!input) {
        return NULL;
    }
    TupleList *result = create_tuple_list(input->capacity);
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < input->count; ++i) {
        int id = input->tuples[i].id;
        int found = 0;
        for (size_t j = 0; j < result->count; ++j) {
            if (result->tuples[j].id == id) {
                size_t old_num = result->tuples[j].num_values;
                size_t add_num = input->tuples[i].num_values;
                int *new_values = realloc(result->tuples[j].values, (old_num + add_num) * sizeof(int));
                if (!new_values) {
                    free_tuple_list(result);
                    return NULL;
                }
                memcpy(new_values + old_num, input->tuples[i].values, add_num * sizeof(int));
                result->tuples[j].values = new_values;
                result->tuples[j].num_values = old_num + add_num;
                found = 1;
                break;
            }
        }
        if (!found) {
            if (add_tuple(result, id, input->tuples[i].values, input->tuples[i].num_values) != 0) {
                free_tuple_list(result);
                return NULL;
            }
        }
    }
    return result;
}

void print_tuple_list(const TupleList *list) {
    if (!list) {
        return;
    }
    for (size_t i = 0; i < list->count; ++i) {
        printf("[%d", list->tuples[i].id);
        for (size_t j = 0; j < list->tuples[i].num_values; ++j) {
            printf(", %d", list->tuples[i].values[j]);
        }
        printf("]\n");
    }
}

int main(void) {
    TupleList *input = create_tuple_list(4);
    if (!input) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Variable 'vals1' can be declared as const array [constVariable]
     */
    int vals1[] = {1, 2};
    /* Possible weaknesses found:
     *  Variable 'vals2' can be declared as const array [constVariable]
     */
    int vals2[] = {3};
    /* Possible weaknesses found:
     *  Variable 'vals3' can be declared as const array [constVariable]
     */
    int vals3[] = {4, 5, 6};
    /* Possible weaknesses found:
     *  Variable 'vals4' can be declared as const array [constVariable]
     */
    int vals4[] = {7};

    if (add_tuple(input, 1, vals1, 2) != 0 ||
        add_tuple(input, 2, vals2, 1) != 0 ||
        add_tuple(input, 1, vals3, 3) != 0 ||
        add_tuple(input, 3, vals4, 1) != 0) {
        free_tuple_list(input);
        return EXIT_FAILURE;
    }

    TupleList *joined = join_tuples(input);
    if (!joined) {
        free_tuple_list(input);
        return EXIT_FAILURE;
    }

    print_tuple_list(joined);

    free_tuple_list(input);
    free_tuple_list(joined);

    return EXIT_SUCCESS;
}