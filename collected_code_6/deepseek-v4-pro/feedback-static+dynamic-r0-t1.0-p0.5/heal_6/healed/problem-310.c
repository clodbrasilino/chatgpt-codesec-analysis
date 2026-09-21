#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

Tuple string_to_tuple(const char *str) {
    Tuple tuple;
    tuple.items = NULL;
    tuple.count = 0;

    if (str == NULL) {
        return tuple;
    }

    size_t len = strnlen(str, 4096);
    if (len == 0 || len >= 4096) {
        return tuple;
    }

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return tuple;
    }

    memcpy(copy, str, len + 1);

    size_t capacity = 4;
    tuple.items = malloc(capacity * sizeof(char *));
    if (tuple.items == NULL) {
        free(copy);
        tuple.items = NULL;
        tuple.count = 0;
        return tuple;
    }

    char *saveptr;
    char *token = strtok_r(copy, ",", &saveptr);
    while (token != NULL) {
        while (*token == ' ') token++;
        
        size_t token_len = strnlen(token, 4096);
        if (token_len >= 4096) {
            for (size_t i = 0; i < tuple.count; i++) {
                free(tuple.items[i]);
            }
            free(tuple.items);
            free(copy);
            tuple.items = NULL;
            tuple.count = 0;
            return tuple;
        }

        if (token_len == 0) {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        char *end = token + token_len;
        while (end > token && *(end - 1) == ' ') {
            end--;
        }
        *end = '\0';
        token_len = (size_t)(end - token);

        if (token_len == 0) {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        if (tuple.count == capacity) {
            if (capacity > SIZE_MAX / 2 / sizeof(char *)) {
                for (size_t i = 0; i < tuple.count; i++) {
                    free(tuple.items[i]);
                }
                free(tuple.items);
                free(copy);
                tuple.items = NULL;
                tuple.count = 0;
                return tuple;
            }
            size_t new_capacity = capacity * 2;
            char **new_items = realloc(tuple.items, new_capacity * sizeof(char *));
            if (new_items == NULL) {
                for (size_t i = 0; i < tuple.count; i++) {
                    free(tuple.items[i]);
                }
                free(tuple.items);
                free(copy);
                tuple.items = NULL;
                tuple.count = 0;
                return tuple;
            }
            tuple.items = new_items;
            capacity = new_capacity;
        }

        tuple.items[tuple.count] = malloc(token_len + 1);
        if (tuple.items[tuple.count] == NULL) {
            for (size_t i = 0; i < tuple.count; i++) {
                free(tuple.items[i]);
            }
            free(tuple.items);
            free(copy);
            tuple.items = NULL;
            tuple.count = 0;
            return tuple;
        }

        memcpy(tuple.items[tuple.count], token, token_len + 1);

        tuple.count++;
        token = strtok_r(NULL, ",", &saveptr);
    }

    free(copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    tuple->items = NULL;
    tuple->count = 0;
}

int main(void) {
    const char *input = "apple, banana, cherry, date";
    Tuple result = string_to_tuple(input);

    if (result.items == NULL && result.count == 0) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return 1;
    }

    printf("Tuple contains %zu items:\n", result.count);
    for (size_t i = 0; i < result.count; i++) {
        printf("  [%zu] %s\n", i, result.items[i]);
    }

    free_tuple(&result);
    return 0;
}