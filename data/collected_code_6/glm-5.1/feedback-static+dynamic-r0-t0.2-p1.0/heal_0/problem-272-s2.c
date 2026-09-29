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

int list_init(TupleList *list, size_t capacity) {
    list->data = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list->data == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = capacity;
    return 0;
}

void list_free(TupleList *list) {
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

int list_append(TupleList *list, Tuple tuple) {
    if (list->size == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 1 : list->capacity * 2;
        Tuple *new_data = (Tuple *)realloc(list->data, new_capacity * sizeof(Tuple));
        if (new_data == NULL) {
            return -1;
        }
        list->data = new_data;
        list->capacity = new_capacity;
    }
    list->data[list->size] = tuple;
    list->size++;
    return 0;
}

int extract_rear(TupleList *list, Tuple *out) {
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

int main(void) {
    TupleList list;
    if (list_init(&list, 2) != 0) {
        return EXIT_FAILURE;
    }

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};

    if (list_append(&list, t1) != 0 || list_append(&list, t2) != 0 || list_append(&list, t3) != 0) {
        list_free(&list);
        return EXIT_FAILURE;
    }

    Tuple rear;
    if (extract_rear(&list, &rear) == 0) {
        printf("Extracted rear: (%d, %d)\n", rear.a, rear.b);
    } else {
        list_free(&list);
        return EXIT_FAILURE;
    }

    if (extract_rear(&list, &rear) == 0) {
        printf("Extracted rear: (%d, %d)\n", rear.a, rear.b);
    } else {
        list_free(&list);
        return EXIT_FAILURE;
    }

    if (extract_rear(&list, &rear) == 0) {
        printf("Extracted rear: (%d, %d)\n", rear.a, rear.b);
    } else {
        list_free(&list);
        return EXIT_FAILURE;
    }

    if (extract_rear(&list, &rear) != 0) {
        printf("List is empty, extraction correctly failed.\n");
    }

    list_free(&list);
    return EXIT_SUCCESS;
}