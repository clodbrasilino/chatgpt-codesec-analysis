#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t len;
} Tuple;

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->items != NULL) {
        for (size_t i = 0; i < tuple->len; i++) {
            free(tuple->items[i]);
        }
        free(tuple->items);
    }
    free(tuple);
}

Tuple *string_list_to_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strlen(str);
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->len = len;
    if (len == 0) {
        tuple->items = malloc(sizeof(char *));
        if (tuple->items == NULL) {
            free(tuple);
            return NULL;
        }
        tuple->items[0] = NULL;
        return tuple;
    }
    tuple->items = malloc((len + 1) * sizeof(char *));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        tuple->items[i] = malloc(2 * sizeof(char));
        if (tuple->items[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(tuple->items[j]);
            }
            free(tuple->items);
            free(tuple);
            return NULL;
        }
        tuple->items[i][0] = str[i];
        tuple->items[i][1] = '\0';
    }
    tuple->items[len] = NULL;
    return tuple;
}

int main(int argc, char *argv[]) {
    const char *str = "python3.0";
    if (argc > 1) {
        str = argv[1];
    }
    Tuple *tuple = string_list_to_tuple(str);
    if (tuple == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }
    printf("[");
    for (size_t i = 0; i < tuple->len; i++) {
        printf("'%s'", tuple->items[i]);
        if (i < tuple->len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    free_tuple(tuple);
    return EXIT_SUCCESS;
}