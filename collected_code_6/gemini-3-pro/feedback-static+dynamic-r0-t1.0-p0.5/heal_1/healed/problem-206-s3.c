#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **elements;
    size_t size;
} Tuple;

Tuple* concatenate_adjacent(const Tuple *input) {
    if (!input || !input->elements || input->size == 0) {
        return NULL;
    }

    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    if (!result) {
        return NULL;
    }

    if (input->size == 1) {
        result->size = 1;
        result->elements = (char **)malloc(sizeof(char *));
        if (!result->elements) {
            free(result);
            return NULL;
        }
        result->elements[0] = strdup(input->elements[0]);
        if (!result->elements[0]) {
            free(result->elements);
            free(result);
            return NULL;
        }
        return result;
    }

    result->size = input->size - 1;
    result->elements = (char **)malloc(result->size * sizeof(char *));
    if (!result->elements) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < result->size; i++) {
        size_t len1 = strlen(input->elements[i]);
        size_t len2 = strlen(input->elements[i + 1]);
        size_t total_len = len1 + len2 + 1;
        
        result->elements[i] = (char *)malloc(total_len);
        if (!result->elements[i]) {
            for (size_t j = 0; j < i; j++) {
                free(result->elements[j]);
            }
            free(result->elements);
            free(result);
            return NULL;
        }
        snprintf(result->elements[i], total_len, "%s%s", input->elements[i], input->elements[i + 1]);
    }

    return result;
}

void free_tuple(Tuple *t) {
    if (t) {
        if (t->elements) {
            for (size_t i = 0; i < t->size; i++) {
                free(t->elements[i]);
            }
            free(t->elements);
        }
        free(t);
    }
}

int main(void) {
    Tuple input;
    input.size = 4;
    input.elements = (char **)malloc(input.size * sizeof(char *));
    if (!input.elements) {
        return 1;
    }

    input.elements[0] = strdup("A");
    input.elements[1] = strdup("B");
    input.elements[2] = strdup("C");
    input.elements[3] = strdup("D");

    for (size_t i = 0; i < input.size; i++) {
        if (!input.elements[i]) {
            for (size_t j = 0; j < i; j++) {
                free(input.elements[j]);
            }
            free(input.elements);
            return 1;
        }
    }

    Tuple *result = concatenate_adjacent(&input);
    if (result) {
        for (size_t i = 0; i < result->size; i++) {
            printf("%s\n", result->elements[i]);
        }
        free_tuple(result);
    }

    for (size_t i = 0; i < input.size; i++) {
        free(input.elements[i]);
    }
    free(input.elements);

    return 0;
}