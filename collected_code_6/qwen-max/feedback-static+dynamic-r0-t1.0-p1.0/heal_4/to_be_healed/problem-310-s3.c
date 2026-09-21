#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** elements;
    int size;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple* string_to_tuple(const char* input) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    const char* delimiter = ",";
    char* input_copy = strdup(input);
    if (input_copy == NULL) {
        free(tuple);
        return NULL;
    }
    char* token = strtok(input_copy, delimiter);
    int count = 0;
    while (token) {
        count++;
        token = strtok(NULL, delimiter);
    }

    tuple->size = count;
    tuple->elements = (char**)malloc(tuple->size * sizeof(char*));
    if (tuple->elements == NULL) {
        free(tuple);
        free(input_copy);
        return NULL;
    }

    token = strtok(input_copy, delimiter);
    for (int i = 0; i < tuple->size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(token);
        tuple->elements[i] = (char*)malloc(len + 1);
        if (tuple->elements[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            free(input_copy);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(tuple->elements[i], token, len);
        tuple->elements[i][len] = '\0';
        token = strtok(NULL, delimiter);
    }

    free(input_copy);
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple) {
        for (int i = 0; i < tuple->size; i++) {
            free(tuple->elements[i]);
        }
        free(tuple->elements);
        free(tuple);
    }
}

int main() {
    const char* input = "apple,banana,orange";
    Tuple* result = string_to_tuple(input);
    if (result) {
        for (int i = 0; i < result->size; i++) {
            printf("%s\n", result->elements[i]);
        }
        free_tuple(result);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}