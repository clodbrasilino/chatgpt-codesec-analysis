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

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len < 2 || str[0] != '(' || str[len - 1] != ')') {
        free(tuple);
        return NULL;
    }

    char* str_copy = malloc(len);
    if (str_copy == NULL) {
        free(tuple);
        return NULL;
    }
    
    for (size_t i = 1; i < len - 1; i++) {
        str_copy[i - 1] = str[i];
    }
    str_copy[len - 2] = '\0';

    char* token = strtok(str_copy, ",");
    while (token != NULL) {
        while (isspace((unsigned char)*token)) {
            token++;
        }
        
        char* end = token;
        while (*end != '\0') {
            end++;
        }
        if (end > token) {
            end--;
        }

        while (end > token && isspace((unsigned char)*end)) {
            *end = '\0';
            end--;
        }

        if (end > token && ((*token == '\'' && *end == '\'') || (*token == '"' && *end == '"'))) {
            token++;
            *end = '\0';
            /* Possible weaknesses found:
             *  Variable 'end' is assigned a value that is never used. [unreadVariable]
             */
            end--;
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

        size_t token_len = 0;
        while (token[token_len] != '\0') {
            token_len++;
        }

        tuple->elements[tuple->count] = malloc(token_len + 1);
        if (tuple->elements[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }

        for (size_t i = 0; i <= token_len; i++) {
            tuple->elements[tuple->count][i] = token[i];
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

int main(void) {
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