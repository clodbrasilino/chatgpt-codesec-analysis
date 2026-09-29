#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** elements;
    int size;
} Tuple;

Tuple* string_to_tuple(const char* input) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    const char* delimiter = ",";
    char* input_copy = strdup(input);
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
        if (token) {
            tuple->elements[i] = strndup(token, strlen(token) + 1);
            if (tuple->elements[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(tuple->elements[j]);
                }
                free(tuple->elements);
                free(tuple);
                free(input_copy);
                return NULL;
            }
        } else {
            free(tuple->elements);
            free(tuple);
            free(input_copy);
            return NULL;
        }
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