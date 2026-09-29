#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char** elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  */

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

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        char* end = token + strlen(token) - 1;
        
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

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t token_len = strlen(token);
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

int main(void) {
    char *input = NULL;
    size_t size = 0;
    ssize_t chars_read = getline(&input, &size, stdin);
    
    if (chars_read > 0) {
        while (chars_read > 0 && (input[chars_read - 1] == '\n' || input[chars_read - 1] == '\r')) {
            input[chars_read - 1] = '\0';
            chars_read--;
        }

        Tuple* tuple = string_to_tuple(input);
        if (tuple != NULL) {
            print_tuple_like_list(tuple);
            free_tuple(tuple);
        }
    }
    
    free(input);
    return 0;
}