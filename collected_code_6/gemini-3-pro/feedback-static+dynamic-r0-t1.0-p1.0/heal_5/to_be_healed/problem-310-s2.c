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

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    Tuple* tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (len == 0) {
        return tuple;
    }

    if (str[0] != '(' || str[len - 1] != ')') {
        tuple->elements = malloc(len * sizeof(char*));
        if (tuple->elements == NULL) {
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < len; i++) {
            tuple->elements[i] = malloc(2);
            if (tuple->elements[i]) {
                tuple->elements[i][0] = str[i];
                tuple->elements[i][1] = '\0';
            }
        }
        tuple->count = len;
        return tuple;
    }

    if (len < 2) {
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
        while (isspace((unsigned char)*token)) token++;
        
        if (*token == '\0') {
            token = strtok(NULL, ",");
            continue;
        }

        char* end = token;
        while (*end != '\0') end++;
        end--;
        
        while (end > token && isspace((unsigned char)*end)) end--;
        end[1] = '\0';

        if (end > token && ((*token == '\'' && *end == '\'') || (*token == '"' && *end == '"'))) {
            token++;
            *end = '\0';
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
        while (token[token_len] != '\0') token_len++;

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

void print_tuple_like_list(Tuple* tuple) {
    if (tuple == NULL) return;
    printf("[");
    for (size_t i = 0; i < tuple->count; i++) {
        printf("'%s'", tuple->elements[i]);
        if (i < tuple->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
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

/* Possible weaknesses found:
 *  to match this '{'
 */
int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];
    
    /* Possible weaknesses found:
     *  to match this '{'
     */
    if (fgets(input, sizeof(input), stdin)) {
        size_t len = 0;
        while (input[len] != '\0') len++;

        /* Possible weaknesses found:
         *  to match this '{'
         *  Unmatched '{'. Configuration: ''. [syntaxError]
         */
        while (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r')) {
            input[len - 1] = '\0';
            /* Possible weaknesses found:
             *  expected ';' at end of input
             *  expected declaration or statement at end of input
             *  expected '}'
             *  expected ';' after expression
             */
            len