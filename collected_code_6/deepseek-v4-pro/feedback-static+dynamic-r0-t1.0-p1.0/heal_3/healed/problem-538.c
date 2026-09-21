#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Tuple {
    char **items;
    size_t size;
} Tuple;

Tuple *string_list_to_tuple(char **list, size_t count) {
    if (list == NULL && count > 0) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = count;
    if (count == 0) {
        tuple->items = NULL;
        return tuple;
    }

    tuple->items = malloc(count * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = 0;
            const char *ptr = list[i];
            while (len < SIZE_MAX && *ptr != '\0') {
                len++;
                ptr++;
            }
            if (len == SIZE_MAX && *ptr != '\0') {
                for (size_t j = 0; j < i; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }

            tuple->items[i] = malloc(len + 1);
            if (tuple->items[i] == NULL) {
                for (size_t j = 0; j < i; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }

            for (size_t k = 0; k <= len; k++) {
                tuple->items[i][k] = list[i][k];
            }
        } else {
            tuple->items[i] = NULL;
        }
    }

    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }

    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }

    free(tuple);
}

int main(void) {
    char *string_list[] = {"apple", "banana", "cherry", NULL, "elderberry"};
    size_t list_size = sizeof(string_list) / sizeof(string_list[0]);

    Tuple *tuple = string_list_to_tuple(string_list, list_size);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to create tuple\n");
        return 1;
    }

    printf("Tuple contents (%zu items):\n", tuple->size);
    for (size_t i = 0; i < tuple->size; i++) {
        if (tuple->items[i] != NULL) {
            printf("[%zu] %s\n", i, tuple->items[i]);
        } else {
            printf("[%zu] NULL\n", i);
        }
    }

    free_tuple(tuple);
    return 0;
}