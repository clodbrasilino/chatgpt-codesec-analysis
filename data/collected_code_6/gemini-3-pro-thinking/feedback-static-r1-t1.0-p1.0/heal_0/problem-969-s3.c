#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
    size_t capacity;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
    size_t capacity;
} TupleList;

TupleList* create_tuple_list(size_t capacity);
void free_tuple_list(TupleList *list);
int append_to_tuple(Tuple *tuple, int element);
int add_tuple_to_list(TupleList *list, const Tuple *tuple);
TupleList* join_tuples(const TupleList *input);

TupleList* create_tuple_list(size_t capacity) {
    TupleList *list = malloc(sizeof(TupleList));
    if (!list) {
        return NULL;
    }
    
    if (capacity > 0) {
        list->tuples = malloc(capacity * sizeof(Tuple));
        if (!list->tuples) {
            free(list);
            return NULL;
        }
    } else {
        list->tuples = NULL;
    }
    
    list->count = 0;
    list->capacity = capacity;
    return list;
}

void free_tuple_list(TupleList *list) {
    if (!list) {
        return;
    }
    
    for (size_t i = 0; i < list->count; i++) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    free(list);
}

int append_to_tuple(Tuple *tuple, int element) {
    if (tuple->count >= tuple->capacity) {
        size_t new_capacity = tuple->capacity == 0 ? 2 : tuple->capacity * 2;
        int *new_elements = realloc(tuple->elements, new_capacity * sizeof(int));
        if (!new_elements) {
            return -1;
        }
        tuple->elements = new_elements;
        tuple->capacity = new_capacity;
    }
    tuple->elements[tuple->count++] = element;
    return 0;
}

int add_tuple_to_list(TupleList *list, const Tuple *tuple) {
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 2 : list->capacity * 2;
        Tuple *new_tuples = realloc(list->tuples, new_capacity * sizeof(Tuple));
        if (!new_tuples) {
            return -1;
        }
        list->tuples = new_tuples;
        list->capacity = new_capacity;
    }
    
    Tuple *new_tuple = &list->tuples[list->count];
    new_tuple->elements = NULL;
    new_tuple->count = 0;
    new_tuple->capacity = 0;
    
    if (tuple->count > 0) {
        new_tuple->elements = malloc(tuple->count * sizeof(int));
        if (!new_tuple->elements) {
            return -1;
        }
        for (size_t i = 0; i < tuple->count; i++) {
            new_tuple->elements[i] = tuple->elements[i];
        }
        new_tuple->count = tuple->count;
        new_tuple->capacity = tuple->count;
    }
    
    list->count++;
    return 0;
}

TupleList* join_tuples(const TupleList *input) {
    if (!input) {
        return NULL;
    }

    TupleList *result = create_tuple_list(input->count);
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < input->count; i++) {
        if (input->tuples[i].count == 0) {
            continue;
        }

        int initial_element = input->tuples[i].elements[0];
        int found = 0;

        for (size_t j = 0; j < result->count; j++) {
            if (result->tuples[j].count > 0 && result->tuples[j].elements[0] == initial_element) {
                for (size_t k = 1; k < input->tuples[i].count; k++) {
                    if (append_to_tuple(&result->tuples[j], input->tuples[i].elements[k]) != 0) {
                        free_tuple_list(result);
                        return NULL;
                    }
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            if (add_tuple_to_list(result, &input->tuples[i]) != 0) {
                free_tuple_list(result);
                return NULL;
            }
        }
    }
    return result;
}

int main(void) {
    TupleList *input = create_tuple_list(4);
    if (!input) {
        return 1;
    }

    Tuple t1 = {NULL, 0, 0};
    Tuple t2 = {NULL, 0, 0};
    Tuple t3 = {NULL, 0, 0};

    if (append_to_tuple(&t1, 1) != 0 || append_to_tuple(&t1, 2) != 0 ||
        append_to_tuple(&t2, 1) != 0 || append_to_tuple(&t2, 3) != 0 ||
        append_to_tuple(&t3, 2) != 0 || append_to_tuple(&t3, 4) != 0) {
        free(t1.elements);
        free(t2.elements);
        free(t3.elements);
        free_tuple_list(input);
        return 1;
    }

    if (add_tuple_to_list(input, &t1) != 0 ||
        add_tuple_to_list(input, &t2) != 0 ||
        add_tuple_to_list(input, &t3) != 0) {
        free(t1.elements);
        free(t2.elements);
        free(t3.elements);
        free_tuple_list(input);
        return 1;
    }

    free(t1.elements);
    free(t2.elements);
    free(t3.elements);

    TupleList *joined = join_tuples(input);
    if (!joined) {
        free_tuple_list(input);
        return 1;
    }

    for (size_t i = 0; i < joined->count; i++) {
        printf("(");
        for (size_t j = 0; j < joined->tuples[i].count; j++) {
            printf("%d", joined->tuples[i].elements[j]);
            if (j < joined->tuples[i].count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    free_tuple_list(input);
    free_tuple_list(joined);
    return 0;
}