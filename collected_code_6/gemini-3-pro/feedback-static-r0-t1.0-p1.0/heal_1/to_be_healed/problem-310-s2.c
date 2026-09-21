#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char** elements;
    size_t count;
} Tuple;

Tuple* string_to_tuple(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    Tuple* tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len < 2 || str[0] != '(' || str[len - 1] != ')') {
        free(tuple);
        return NULL;
    }

    char* str_copy = strdup(str + 1);
    if (str_copy == NULL) {
        free(tuple);
        return NULL;
    }
    str_copy[len - 2] = '\0';

    char* token = strtok(str_copy, ",");
    while (token != NULL) {
        while (isspace((unsigned char)*token)) token++;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        char* end = token + strlen(token) - 1;
        while (end > token && isspace((unsigned char)*end)) end--;
        end[1] = '\0';

        if (*token == '\'' && *end == '\'') {
            token++;
            end[-1] = '\0';
        } else if (*token == '"' && *end == '"') {
            token++;
            end[-1] = '\0';
        }

        char** new_elements = realloc(tuple->elements, (tuple->count + 1) * sizeof(char*));
        if (new_elements == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        tuple->elements = new_elements;

        tuple->elements[tuple->count] = strdup(token);
        if (tuple->elements[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        tuple->count++;

        token = strtok(NULL, ",");
    }

    free(str_copy);
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main() {
    const char* str = "(1, 'hello', 3.14, \"world\")";
    Tuple* tuple = string_to_tuple(str);

    if (tuple != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            printf("Element %zu: %s\n", i, tuple->elements[i]);
        }
        free_tuple(tuple);
    } else {
        printf("Failed to parse tuple.\n");
    }

    return 0;
}