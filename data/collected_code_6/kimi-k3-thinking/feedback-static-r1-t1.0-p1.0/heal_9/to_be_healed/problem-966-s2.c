#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

static size_t safe_count(const TupleList *list) {
    if (list == NULL || list->items == NULL) {
        return 0;
    }
    if (list->count > list->capacity) {
        return list->capacity;
    }
    return list->count;
}

int init_tuple_list(TupleList *list, size_t capacity) {
    if (list == NULL) {
        return -1;
    }
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
    if (capacity == 0) {
        return 0;
    }
    if (capacity > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    list->items = (Tuple *)calloc(capacity, sizeof(Tuple));
    if (list->items == NULL) {
        return -1;
    }
    list->capacity = capacity;
    return 0;
}

Tuple create_tuple(const int *data, size_t size) {
    Tuple t;
    t.data = NULL;
    t.size = 0;
    if (data == NULL || size == 0) {
        return t;
    }
    if (size > SIZE_MAX / sizeof(int)) {
        return t;
    }
    size_t bytes = size * sizeof(int);
    int *buffer = (int *)malloc(bytes);
    if (buffer == NULL) {
        return t;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, data, bytes);
    t.data = buffer;
    t.size = size;
    return t;
}

int add_tuple(TupleList *list, Tuple t) {
    if (list == NULL) {
        return -1;
    }
    if (list->count > list->capacity) {
        return -1;
    }
    if (list->count == list->capacity) {
        size_t new_capacity;
        if (list->capacity == 0) {
            new_capacity = 4;
        } else {
            if (list->capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = list->capacity * 2;
        }
        if (new_capacity > SIZE_MAX / sizeof(Tuple)) {
            return -1;
        }
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    if (list->items == NULL || list->count >= list->capacity) {
        return -1;
    }
    list->items[list->count] = t;
    list->count++;
    return 0;
}

int add_tuple_data(TupleList *list, const int *data, size_t size) {
    if (list == NULL) {
        return -1;
    }
    Tuple t = create_tuple(data, size);
    if (data != NULL && size > 0 && t.data == NULL) {
        return -1;
    }
    if (add_tuple(list, t) != 0) {
        free(t.data);
        return -1;
    }
    return 0;
}

size_t remove_empty_tuples(TupleList *list) {
    if (list == NULL || list->items == NULL || list->capacity == 0) {
        return 0;
    }
    size_t count = safe_count(list);
    size_t write = 0;
    size_t removed = 0;
    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    for (size_t read = 0; read < count; read++) {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (list->items[read].data != NULL && list->items[read].size > 0) {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            if (write != read) {
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                list->items[write] = list->items[read];
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                list->items[read].data = NULL;
                /* Possible weaknesses found:
                 * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                list->items[read].size = 0;
            }
            write++;
        } else {
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            free(list->items[read].data);
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            list->items[read].data = NULL;
            /* Possible weaknesses found:
             * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            list->items[read].size = 0;
            removed++;
        }
    }
    list->count = write;
    return removed;
}

void print_tuple_list(const TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->items == NULL || list->capacity == 0) {
        printf("[]\n");
        return;
    }
    size_t count = safe_count(list);
    printf("[");
    for (size_t i = 0; i < count; i++) {
        printf("(");
        if (list->items[i].data != NULL && list->items[i].size > 0) {
            for (size_t j = 0; j < list->items[i].size; j++) {
                printf("%d", list->items[i].data[j]);
                if (j + 1 < list->items[i].size) {
                    printf(", ");
                }
            }
        }
        printf(")");
        if (i + 1 < count) {
            printf(", ");
        }
    }
    printf("]\n");
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        size_t count = safe_count(list);
        for (size_t i = 0; i < count; i++) {
            free(list->items[i].data);
            list->items[i].data = NULL;
            list->items[i].size = 0;
        }
        free(list->items);
    }
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

int main(void) {
    TupleList list;
    if (init_tuple_list(&list, 0) != 0) {
        fprintf(stderr, "Error: failed to initialize tuple list.\n");
        return EXIT_FAILURE;
    }

    const int d1[] = {1, 2, 3};
    const int d2[] = {4, 5};
    const int d3[] = {7, 8, 9, 10};

    if (add_tuple_data(&list, d1, 3) != 0 ||
        add_tuple_data(&list, NULL, 0) != 0 ||
        add_tuple_data(&list, d2, 2) != 0 ||
        add_tuple_data(&list, NULL, 0) != 0 ||
        add_tuple_data(&list, d3, 4) != 0) {
        fprintf(stderr, "Error: failed to add tuple.\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Original list: ");
    print_tuple_list(&list);

    size_t removed = remove_empty_tuples(&list);

    printf("Removed %zu empty tuple(s).\n", removed);
    printf("Updated list:  ");
    print_tuple_list(&list);

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}