#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t len;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
} TupleList;

int trim_tuple_list(TupleList *list, size_t k) {
    if (list == NULL) {
        return -1;
    }
    for (size_t i = 0; i < list->count; i++) {
        Tuple *t = &list->items[i];
        if (k <= t->len / 2) {
            size_t new_len = t->len - 2 * k;
            if (new_len == 0) {
                free(t->data);
                t->data = NULL;
                t->len = 0;
            } else {
                if (new_len > SIZE_MAX / sizeof(int)) {
                    return -2;
                }
                size_t alloc_size = new_len * sizeof(int);
                /* Possible weaknesses found:
                 *  'dest_size' is assigned value 'alloc_size' here.
                 */
                size_t dest_size = alloc_size;
                size_t src_size = (t->len - k) * sizeof(int);
                /* Possible weaknesses found:
                 *  The comparison 'alloc_size > dest_size' is always false because 'alloc_size' and 'dest_size' represent the same value. [knownConditionTrueFalse]
                 *  The comparison 'alloc_size > dest_size' is always false because 'alloc_size' and 'dest_size' represent the same value.
                 */
                if (alloc_size > dest_size || alloc_size > src_size) {
                    return -2;
                }
                int *new_data = malloc(alloc_size);
                if (new_data == NULL) {
                    return -2;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(new_data, t->data + k, alloc_size);
                free(t->data);
                t->data = new_data;
                t->len = new_len;
            }
        } else {
            free(t->data);
            t->data = NULL;
            t->len = 0;
        }
    }
    return 0;
}

void free_tuple_list(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        for (size_t i = 0; i < list->count; i++) {
            free(list->items[i].data);
        }
        free(list->items);
    }
}

int main(void) {
    TupleList list;
    list.count = 3;
    list.items = calloc(list.count, sizeof(Tuple));
    if (list.items == NULL) {
        return EXIT_FAILURE;
    }

    list.items[0].len = 6;
    list.items[0].data = malloc(list.items[0].len * sizeof(int));
    if (list.items[0].data == NULL) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < list.items[0].len; i++) {
        list.items[0].data[i] = (int)i + 1;
    }

    list.items[1].len = 5;
    list.items[1].data = malloc(list.items[1].len * sizeof(int));
    if (list.items[1].data == NULL) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < list.items[1].len; i++) {
        list.items[1].data[i] = (int)i + 10;
    }

    list.items[2].len = 4;
    list.items[2].data = malloc(list.items[2].len * sizeof(int));
    if (list.items[2].data == NULL) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < list.items[2].len; i++) {
        list.items[2].data[i] = (int)i + 100;
    }

    size_t k = 1;
    int rc = trim_tuple_list(&list, k);
    if (rc != 0) {
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; i++) {
        for (size_t j = 0; j < list.items[i].len; j++) {
            printf("%d ", list.items[i].data[j]);
        }
        printf("\n");
    }

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}