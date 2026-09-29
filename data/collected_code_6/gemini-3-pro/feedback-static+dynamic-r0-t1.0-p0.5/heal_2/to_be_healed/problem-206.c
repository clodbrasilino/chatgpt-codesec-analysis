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
        
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(input->elements[0]);
        result->elements[0] = (char *)malloc(len + 1);
        if (!result->elements[0]) {
            free(result->elements);
            free(result);
            return NULL;
        }
        snprintf(result->elements[0], len + 1, "%s", input->elements[0]);
        
        return result;
    }

    result->size = input->size - 1;
    result->elements = (char **)malloc(result->size * sizeof(char *));
    if (!result->elements) {
        free(result);
        return NULL;
    }

    for (size_t i = 0; i < result->size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len1 = strlen(input->elements[i]);
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
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

    const char *initial_values[] = {"A", "B", "C", "D"};
    for (size_t i = 0; i < input.size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(initial_values[i]);
        input.elements[i] = (char *)malloc(len + 1);
        if (input.elements[i]) {
            snprintf(input.elements[i], len + 1, "%s", initial_values[i]);
        }
    }

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