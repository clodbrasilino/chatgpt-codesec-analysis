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

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->elements = NULL;
    tuple->count = 0;

    if (len == 0) {
        return tuple;
    }

    if (str[0] != '(' || str[len - 1] != ')') {
        tuple->elements = (char**)malloc(len * sizeof(char*));
        if (tuple->elements == NULL) {
            free(tuple);
            return NULL;
        }
        for (size_t i = 0; i < len; i++) {
            tuple->elements[i] = (char*)malloc(2);
            if (tuple->elements[i] != NULL) {
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

    char* str_copy = (char*)malloc(len);
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
        
        if (*token == '\0') {
            token = strtok(NULL, ",");
            continue;
        }

        size_t t_len = 0;
        while (token[t_len] != '\0') {
            t_len++;
        }

        char* end = token + t_len - 1;
        while (end > token && isspace((unsigned char)*end)) {
            end--;
        }
        end[1] = '\0';

        if (end > token && ((*token == '\'' && *end == '\'') || (*token == '"' && *end == '"'))) {
            token++;
            *end = '\0';
        }

        char** new_elements = (char**)realloc(tuple->elements, (tuple->count + 1) * sizeof(char*));
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

        tuple->elements[tuple->count] = (char*)malloc(token_len + 1);
        if (tuple->elements[tuple->count] == NULL) {
            for (size_t i = 0; i < tuple->count; i++) {
                free(tuple->elements[i]);
            }
            free(tuple->elements);
            free(tuple);
            free(str_copy);
            return NULL;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->elements[tuple->count], token, token_len + 1);
        tuple->count++;

        token = strtok(NULL, ",");
    }

    free(str_copy);
    return tuple;
}

void print_tuple_like_list(Tuple* tuple) {
    if (tuple == NULL) {
        return;
    }
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
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 */
int main(void) {
    size_t capacity = 256;
    size_t length = 0;
    char* input = (char*)malloc(capacity);
    
    if (input == NULL) {
        return 1;
    }
    
    int c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r') {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* new_input = (char*)realloc(input, capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }
            input = new_input;
        }
        input[length++] = (char)c;
    }
    /* Possible weaknesses found:
     *  expected ']'
     *  expected '}'
     *  expected ']' at end of input
     *  to match this '['
     *  expected declaration or statement at end of input
     */
    input[length