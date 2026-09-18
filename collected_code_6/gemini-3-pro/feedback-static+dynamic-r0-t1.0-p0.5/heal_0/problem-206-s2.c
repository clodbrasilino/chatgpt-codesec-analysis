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

    for (size_t i = 0; i < result->size; ++i) {
        if (!input->elements[i] || !input->elements[i + 1]) {
            for (size_t j = 0; j < i; ++j) {
                free(result->elements[j]);
            }
            free(result->elements);
            free(result);
            return NULL;
        }

        size_t len1 = strlen(input->elements[i]);
        size_t len2 = strlen(input->elements[i + 1]);
        
        result->elements[i] = (char *)malloc(len1 + len2 + 1);
        if (!result->elements[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(result->elements[j]);
            }
            free(result->elements);
            free(result);
            return NULL;
        }
        
        strcpy(result->elements[i], input->elements[i]);
        strcat(result->elements[i], input->elements[i + 1]);
    }

    return result;
}

void free_tuple(Tuple *t) {
    if (t) {
        if (t->elements) {
            for (size_t i = 0; i < t->size; ++i) {
                free(t->elements[i]);
            }
            free(t->elements);
        }
        free(t);
    }
}

int main(void) {
    char *data[] = {"Hello", "World", "From", "C"};
    Tuple input = {data, 4};

    Tuple *result = concatenate_adjacent(&input);
    if (result) {
        for (size_t i = 0; i < result->size; ++i) {
            printf("%s\n", result->elements[i]);
        }
        free_tuple(result);
    }

    return 0;
}