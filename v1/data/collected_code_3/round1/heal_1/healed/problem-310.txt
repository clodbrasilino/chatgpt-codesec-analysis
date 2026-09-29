#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;

Tuple* string_to_tuple(char* str) {
    char* delimiter = " ";
    char* token;
    Tuple* tuple = (Tuple*) malloc(sizeof(Tuple));

    if (tuple == NULL) {
        return NULL;
    }

    token = strtok(str, delimiter);

    if (token != NULL) {
        tuple->first = malloc(strlen(token) + 1);

        if (tuple->first != NULL) {
            strcpy(tuple->first, token);
        } else {
            free(tuple);
            return NULL;
        }

        token = strtok(NULL, delimiter);

        if (token != NULL) {
            tuple->second = malloc(strlen(token) + 1);

            if (tuple->second != NULL) {
                strcpy(tuple->second, token);
            } else {
                free(tuple->first);
                free(tuple);
                return NULL;
            }
        }
    }

    return tuple;
}

int main() {
    char str[] = "Hello World";
    Tuple* tuple = string_to_tuple(str);

    if (tuple != NULL) {
        printf("First: %s, Second: %s\n", tuple->first, tuple->second);
        free(tuple->first);
        free(tuple->second);
        free(tuple);
    }

    return 0;
}