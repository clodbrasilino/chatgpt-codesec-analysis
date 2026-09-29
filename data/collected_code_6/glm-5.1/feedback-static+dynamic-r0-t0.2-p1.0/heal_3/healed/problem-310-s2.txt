#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} Tuple;

size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Tuple *string_to_tuple(const char *str, const char *delim) {
    if (str == NULL || delim == NULL) {
        return NULL;
    }

    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->items = NULL;
    tuple->count = 0;

    size_t str_len = strlen(str);
    char *temp = (char *)malloc(str_len + 1);
    if (temp == NULL) {
        free(tuple);
        return NULL;
    }
    memcpy(temp, str, str_len + 1);

    char *rest = NULL;
    char *token = strtok_r(temp, delim, &rest);
    while (token != NULL) {
        char **new_items = (char **)realloc(tuple->items, (tuple->count + 1) * sizeof(char *));
        if (new_items == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }

        tuple->items = new_items;

        size_t token_len = safe_strlen(token, str_len);
        tuple->items[tuple->count] = (char *)malloc(token_len + 1);
        if (tuple->items[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->items[i]);
            }
            free(tuple->items);
            free(tuple);
            free(temp);
            return NULL;
        }

        for (size_t i = 0; i < token_len; i++) {
            tuple->items[tuple->count][i] = token[i];
        }
        tuple->items[tuple->count][token_len] = '\0';

        tuple->count++;
        token = strtok_r(NULL, delim, &rest);
    }

    if (tuple->items == NULL && tuple->count == 0) {
        char **new_items = (char **)malloc(sizeof(char *));
        if (new_items != NULL) {
            tuple->items = new_items;
        }
    }

    free(temp);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
        free(tuple);
    }
}

int main(void) {
    const char *input = "apple,banana,cherry";
    const char *delimiter = ",";

    Tuple *my_tuple = string_to_tuple(input, delimiter);
    if (my_tuple == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < my_tuple->count; i++) {
        printf("%s\n", my_tuple->items[i]);
    }

    free_tuple(my_tuple);

    return EXIT_SUCCESS;
}