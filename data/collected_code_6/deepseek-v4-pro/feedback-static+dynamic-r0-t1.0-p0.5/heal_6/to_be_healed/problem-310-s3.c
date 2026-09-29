#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    if (len >= 4095) {
        return tuple;
    }

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return tuple;
    }

    if (len > 0) {
        if (len + 1 > len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(copy, str, len + 1);
        }
    } else {
        copy[0] = '\0';
    }

    size_t capacity = 4;
    tuple.items = malloc(capacity * sizeof(char *));
    if (tuple.items == NULL) {
        free(copy);
        return tuple;
    }

    char *saveptr;
    char *token = strtok_r(copy, ",", &saveptr);
    while (token != NULL) {
        while (*token == ' ') token++;
        if (*token == '\0') {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        char *end = token;
        while (*end != '\0') end++;
        end--;
        while (end > token && *end == ' ') {
            *end = '\0';
            end--;
        }

        if (*token == '\0') {
            token = strtok_r(NULL, ",", &saveptr);
            continue;
        }

        size_t tok_len = 0;
        while (token[tok_len] != '\0') tok_len++;

        if (tuple.count >= capacity) {
            capacity *= 2;
            char **new_items = realloc(tuple.items, capacity * sizeof(char *));
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
        }

        tuple.items[tuple.count] = malloc(tok_len + 1);
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

        if (tok_len + 1 > tok_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(tuple.items[tuple.count], token, tok_len + 1);
        }
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
        printf("Failed to convert string to tuple\n");
        return 1;
    }

    printf("Tuple contains %zu items:\n", result.count);
    for (size_t i = 0; i < result.count; i++) {
        printf("  [%zu] = '%s'\n", i, result.items[i]);
    }

    free_tuple(&result);
    return 0;
}