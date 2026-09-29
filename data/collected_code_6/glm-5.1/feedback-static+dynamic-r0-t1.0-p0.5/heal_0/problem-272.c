#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *data;
    size_t size;
    size_t capacity;
} TupleList;

TupleList* tuple_list_create(size_t capacity) {
    TupleList *list = (TupleList*)malloc(sizeof(TupleList));
    if (list == NULL) {
        return NULL;
    }
    list->data = (Tuple*)malloc(capacity * sizeof(Tuple));
    if (list->data == NULL) {
        free(list);
        return NULL;
    }
    list->size = 0;
    list->capacity = capacity;
    return list;
}

int tuple_list_append(TupleList *list, Tuple t) {
    if (list == NULL) {
        return -1;
    }
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;
        Tuple *new_data = (Tuple*)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size] = t;
    list->size++;
    return 0;
}

int tuple_list_extract_rear(TupleList *list, Tuple *out) {
    if (list == NULL || out == NULL) {
        return -1;
    }
    if (list->size == 0) {
        return -1;
    }
    *out = list->data[list->size - 1];
    list->size--;
    return 0;
}

void tuple_list_destroy(TupleList *list) {
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

int main(void) {
    TupleList *list = tuple_list_create(2);
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};

    if (tuple_list_append(list, t1) != 0) {
        tuple_list_destroy(list);
        return EXIT_FAILURE;
    }
    if (tuple_list_append(list, t2) != 0) {
        tuple_list_destroy(list);
        return EXIT_FAILURE;
    }
    if (tuple_list_append(list, t3) != 0) {
        tuple_list_destroy(list);
        return EXIT_FAILURE;
    }

    Tuple rear;
    if (tuple_list_extract_rear(list, &rear) == 0) {
        printf("Extracted rear: (%d, %d)\n", rear.a, rear.b);
    } else {
        tuple_list_destroy(list);
        return EXIT_FAILURE;
    }

    if (tuple_list_extract_rear(list, &rear) == 0) {
        printf("Extracted rear: (%d, %d)\n", rear.a, rear.b);
    } else {
        tuple_list_destroy(list);
        return EXIT_FAILURE;
    }

    if (tuple_list_extract_rear(list, &rear) == 0) {
        printf("Extracted rear: (%d, %d)\n", rear.a, rear.b);
    } else {
        tuple_list_destroy(list);
        return EXIT_FAILURE;
    }

    if (tuple_list_extract_rear(list, &rear) != 0) {
        printf("List is empty, extraction correctly failed.\n");
    }

    tuple_list_destroy(list);
    return EXIT_SUCCESS;
}