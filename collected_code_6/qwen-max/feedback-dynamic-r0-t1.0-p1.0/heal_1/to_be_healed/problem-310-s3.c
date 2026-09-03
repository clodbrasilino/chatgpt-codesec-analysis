#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** elements;
    int size;
} Tuple;
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got ["�","
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  */

Tuple* string_to_tuple(const char* input) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    const char* delimiter = ",";
    char* token = strtok((char*)input, delimiter);
    int count = 0;
    while (token) {
        count++;
        token = strtok(NULL, delimiter);
    }

    tuple->size = count;
    tuple->elements = (char**)malloc(tuple->size * sizeof(char*));
    if (tuple->elements == NULL) {
        free(tuple);
        return NULL;
    }

    token = strtok((char*)input, delimiter);
    for (int i = 0; i < tuple->size; i++) {
        tuple->elements[i] = (char*)malloc(strlen(token) + 1);
        if (tuple->elements[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(tuple->elements[j]);
            }
            free(tuple->elements);
            free(tuple);
            return NULL;
        }
        strcpy(tuple->elements[i], token);
        token = strtok(NULL, delimiter);
    }

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