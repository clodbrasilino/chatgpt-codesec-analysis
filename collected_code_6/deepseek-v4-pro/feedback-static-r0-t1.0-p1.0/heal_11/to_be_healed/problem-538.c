#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Tuple {
    char **items;
    size_t size;
} Tuple;

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Tuple *string_list_to_tuple(char **list, size_t count) {
    if (list == NULL && count > 0) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->size = count;
    if (count == 0) {
        tuple->items = NULL;
        return tuple;
    }

    tuple->items = (char **)calloc(count, sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = safe_strlen(list[i], SIZE_MAX - 1);
            if (len == SIZE_MAX - 1 && list[i][SIZE_MAX - 1] != '\0') {
                for (size_t j = 0; j < i; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }
            tuple->items[i] = (char *)malloc(len + 1);
            if (tuple->items[i] == NULL) {
                for (size_t j = 0; j < i; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }
            if (len + 1 < len) {
                free(tuple->items[i]);
                for (size_t j = 0; j < i; j++) {
                    free(tuple->items[j]);
                }
                free(tuple->items);
                free(tuple);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tuple->items[i], list[i], len);
            tuple->items[i][len] = '\0';
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