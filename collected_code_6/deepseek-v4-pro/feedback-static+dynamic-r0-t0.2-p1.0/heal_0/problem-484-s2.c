#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

void init_tuple_list(TupleList *list) {
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int push_tuple(TupleList *list, Tuple tuple) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Tuple *new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return 0;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size++] = tuple;
    return 1;
}

void free_tuple_list(TupleList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int tuple_equals(Tuple a, Tuple b) {
    return a.first == b.first && a.second == b.second;
}

TupleList remove_matching_tuples(const TupleList *list1, const TupleList *list2) {
    TupleList result;
    init_tuple_list(&result);

    for (size_t i = 0; i < list1->size; i++) {
        int found = 0;
        for (size_t j = 0; j < list2->size; j++) {
            if (tuple_equals(list1->data[i], list2->data[j])) {
                found = 1;
                break;
            }
        }
        if (!found) {
            if (!push_tuple(&result, list1->data[i])) {
                free_tuple_list(&result);
                init_tuple_list(&result);
                return result;
            }
        }
    }

    return result;
}

int main(void) {
    TupleList list1;
    TupleList list2;
    init_tuple_list(&list1);
    init_tuple_list(&list2);

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};
    Tuple t4 = {7, 8};
    Tuple t5 = {3, 4};
    Tuple t6 = {9, 10};

    if (!push_tuple(&list1, t1) || !push_tuple(&list1, t2) ||
        !push_tuple(&list1, t3) || !push_tuple(&list1, t4)) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tuple_list(&list1);
        free_tuple_list(&list2);
        return EXIT_FAILURE;
    }

    if (!push_tuple(&list2, t5) || !push_tuple(&list2, t6) ||
        !push_tuple(&list2, t1)) {
        fprintf(stderr, "Memory allocation failed\n");
        free_tuple_list(&list1);
        free_tuple_list(&list2);
        return EXIT_FAILURE;
    }

    TupleList result = remove_matching_tuples(&list1, &list2);

    printf("Result tuples:\n");
    for (size_t i = 0; i < result.size; i++) {
        printf("(%d, %d)\n", result.data[i].first, result.data[i].second);
    }

    free_tuple_list(&list1);
    free_tuple_list(&list2);
    free_tuple_list(&result);

    return EXIT_SUCCESS;
}