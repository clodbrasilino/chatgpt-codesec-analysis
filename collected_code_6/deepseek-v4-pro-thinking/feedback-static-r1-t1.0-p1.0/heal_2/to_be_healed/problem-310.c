#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

void tuple_free(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
}

int string_to_tuple(const char *str, Tuple *tuple) {
    if (tuple == NULL) {
        return -1;
    }
    tuple->items = NULL;
    tuple->count = 0;

    if (str == NULL) {
        return -1;
    }
    if (str[0] == '\0') {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, str, len + 1);

    size_t capacity = 4;
    char **items = malloc(capacity * sizeof(char *));
    if (items == NULL) {
        free(copy);
        return -1;
    }

    size_t count = 0;
    char *token = strtok(copy, " ,\t\n()");
    while (token != NULL) {
        if (count == capacity) {
            size_t new_capacity = capacity * 2;
            char **new_items = realloc(items, new_capacity * sizeof(char *));
            if (new_items == NULL) {
                for (size_t i = 0; i < count; i++) {
                    free(items[i]);
                }
                free(items);
                free(copy);
                return -1;
            }
            items = new_items;
            capacity = new_capacity;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t tok_len = strlen(token);
        items[count] = malloc(tok_len + 1);
        if (items[count] == NULL) {
            for (size_t i = 0; i < count; i++) {
                free(items[i]);
            }
            free(items);
            free(copy);
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(items[count], token, tok_len + 1);
        count++;
        token = strtok(NULL, " ,\t\n()");
    }

    free(copy);

    if (count == 0) {
        free(items);
        tuple->items = NULL;
        tuple->count = 0;
        return 0;
    }

    tuple->items = items;
    tuple->count = count;
    return 0;
}

int main(void) {
    const char *input = "(hello, world from C)";
    Tuple tuple;

    if (string_to_tuple(input, &tuple) != 0) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tuple.count; i++) {
        printf("%s\n", tuple.items[i]);
    }

    tuple_free(&tuple);
    return EXIT_SUCCESS;
}