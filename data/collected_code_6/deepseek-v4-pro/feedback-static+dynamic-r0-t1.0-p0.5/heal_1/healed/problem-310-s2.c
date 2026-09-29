#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t size;
} Tuple;

Tuple string_to_tuple(const char *str) {
    Tuple tuple;
    tuple.elements = NULL;
    tuple.size = 0;

    if (str == NULL) {
        return tuple;
    }

    size_t len = strnlen(str, 4096);
    if (len == 0 || len == 4096) {
        if (len == 4096) return tuple;
        return tuple;
    }

    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return tuple;
    }
    memcpy(copy, str, len);
    copy[len] = '\0';

    size_t capacity = 4;
    tuple.elements = malloc(capacity * sizeof(char *));
    if (tuple.elements == NULL) {
        free(copy);
        return tuple;
    }

    char *token = strtok(copy, ",");
    while (token != NULL) {
        while (*token == ' ') token++;
        
        size_t token_len = strnlen(token, 4096);
        while (token_len > 0 && token[token_len - 1] == ' ') {
            token[token_len - 1] = '\0';
            token_len--;
        }

        if (tuple.size == capacity) {
            capacity *= 2;
            char **new_elements = realloc(tuple.elements, capacity * sizeof(char *));
            if (new_elements == NULL) {
                for (size_t i = 0; i < tuple.size; i++) {
                    free(tuple.elements[i]);
                }
                free(tuple.elements);
                free(copy);
                tuple.elements = NULL;
                tuple.size = 0;
                return tuple;
            }
            tuple.elements = new_elements;
        }

        tuple.elements[tuple.size] = malloc(token_len + 1);
        if (tuple.elements[tuple.size] == NULL) {
            for (size_t i = 0; i < tuple.size; i++) {
                free(tuple.elements[i]);
            }
            free(tuple.elements);
            free(copy);
            tuple.elements = NULL;
            tuple.size = 0;
            return tuple;
        }
        memcpy(tuple.elements[tuple.size], token, token_len);
        tuple.elements[tuple.size][token_len] = '\0';
        tuple.size++;

        token = strtok(NULL, ",");
    }

    free(copy);
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->size; i++) {
        free(tuple->elements[i]);
    }
    free(tuple->elements);
    tuple->elements = NULL;
    tuple->size = 0;
}

int main(void) {
    const char *input = "apple, banana, cherry, date";
    Tuple result = string_to_tuple(input);

    if (result.elements == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return 1;
    }

    printf("Tuple elements (%zu):\n", result.size);
    for (size_t i = 0; i < result.size; i++) {
        printf("  [%zu] = '%s'\n", i, result.elements[i]);
    }

    free_tuple(&result);
    return 0;
}