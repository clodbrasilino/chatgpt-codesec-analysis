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

    Tuple *result = malloc(sizeof(Tuple));
    if (!result) {
        return NULL;
    }

    if (input->size == 1) {
        result->size = 1;
        result->elements = malloc(sizeof(char*));
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
    result->elements = malloc(result->size * sizeof(char*));
    if (!result->elements) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < result->size; i++) {
        if (!input->elements[i] || !input->elements[i+1]) {
            for (size_t j = 0; j < i; j++) {
                free(result->elements[j]);
            }
            free(result->elements);
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(input->elements[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len2 = strlen(input->elements[i+1]);
        size_t alloc_size = len1 + len2 + 1;
        
        result->elements[i] = malloc(alloc_size);
        if (!result->elements[i]) {
            for (size_t j = 0; j < i; j++) {
                free(result->elements[j]);
            }
            free(result->elements);
            free(result);
            return NULL;
        }
        
        snprintf(result->elements[i], alloc_size, "%s%s", input->elements[i], input->elements[i+1]);
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
    char *elems[] = {"Hello", " ", "World", "!"};
    Tuple input = {elems, 4};

    Tuple *result = concatenate_adjacent(&input);
    if (result) {
        for (size_t i = 0; i < result->size; i++) {
            printf("%s\n", result->elements[i]);
        }
        free_tuple(result);
    }

    return 0;
}