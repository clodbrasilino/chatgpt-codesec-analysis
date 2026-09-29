#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *items;
    size_t count;
} Tuple;

typedef struct {
    Tuple *data;
    size_t count;
    size_t capacity;
} TupleList;

Tuple create_tuple(const int *items, size_t count) {
    Tuple t;
    if (count > 0 && items != NULL) {
        if (count > SIZE_MAX / sizeof(int)) {
            exit(EXIT_FAILURE);
        }
        size_t byte_count = count * sizeof(int);
        t.count = count;
        t.items = malloc(byte_count);
        if (t.items == NULL) {
            exit(EXIT_FAILURE);
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(t.items, items, byte_count);
    } else {
        t.count = 0;
        t.items = NULL;
    }
    return t;
}

void free_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->items);
        t->items = NULL;
        t->count = 0;
    }
}

int remove_empty_tuples(TupleList *list) {
    if (list == NULL || list->data == NULL) {
        return -1;
    }
    size_t write_index = 0;
    for (size_t read_index = 0; read_index < list->count; read_index++) {
        if (list->data[read_index].count == 0) {
            free_tuple(&list->data[read_index]);
        } else {
            if (write_index != read_index) {
                list->data[write_index] = list->data[read_index];
                list->data[read_index].items = NULL;
                list->data[read_index].count = 0;
            }
            write_index++;
        }
    }
    for (size_t i = write_index; i < list->count; i++) {
        list->data[i].items = NULL;
        list->data[i].count = 0;
    }
    list->count = write_index;
    return 0;
}

void free_list(TupleList *list) {
    if (list != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free_tuple(&list->data[i]);
        }
        free(list->data);
        list->data = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int main(void) {
    size_t capacity = 5;
    TupleList list;
    
    if (capacity > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }
    
    list.capacity = capacity;
    list.count = 0;
    list.data = malloc(capacity * sizeof(Tuple));
    
    if (list.data == NULL) {
        return EXIT_FAILURE;
    }

    const int a[] = {1, 2};
    const int b[] = {3};

    list.data[list.count++] = create_tuple(a, 2);
    list.data[list.count++] = create_tuple(NULL, 0);
    list.data[list.count++] = create_tuple(b, 1);
    list.data[list.count++] = create_tuple(NULL, 0);
    list.data[list.count++] = create_tuple(a, 2);

    if (remove_empty_tuples(&list) != 0) {
        free_list(&list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; i++) {
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < list.data[i].count; j++) {
            printf("%d ", list.data[i].items[j]);
        }
        printf("\n");
    }

    free_list(&list);
    return EXIT_SUCCESS;
}