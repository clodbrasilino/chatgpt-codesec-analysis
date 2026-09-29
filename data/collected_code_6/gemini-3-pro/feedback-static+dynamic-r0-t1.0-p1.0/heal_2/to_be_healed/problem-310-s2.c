#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char** elements;
    size_t count;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
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

    char* str_copy = strdup(str + 1);
    if (str_copy == NULL) {
        free(tuple);
        return NULL;
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

    const char* str2 = "python3.0";
    Tuple* tuple2 = string_to_tuple(str2);

    if (tuple2 != NULL) {
        for (size_t i = 0; i < tuple2->count; i++) {
            printf("Element %zu: %s\n", i, tuple2->elements[i]);
        }
        free_tuple(tuple2);
    } else {
        printf("Failed to parse tuple2.\n");
    }

    return 0;
}