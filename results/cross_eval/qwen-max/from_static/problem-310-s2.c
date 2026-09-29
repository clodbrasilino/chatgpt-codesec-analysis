#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;

Tuple* string_to_tuple(const char* input) {
    char* str = strdup(input);
    if (str == NULL) {
        return NULL;
    }

    char* token = strtok(str, " ");
    if (token == NULL) {
        free(str);
        return NULL;
    }

    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    if (tuple == NULL) {
        free(str);
        return NULL;
    }
    tuple->first = token;

    token = strtok(NULL, " ");
    if (token == NULL) {
        free(tuple);
        free(str);
        return NULL;
    }
    tuple->second = token;

    free(str);
    return tuple;
}

void free_tuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple->first);
        free(tuple->second);
        free(tuple);
    }
}

int main() {
    const char* input = "Hello World";
    Tuple* tuple = string_to_tuple(input);

    if (tuple != NULL) {
        printf("First: %s, Second: %s\n", tuple->first, tuple->second);
        free_tuple(tuple);
    } else {
        printf("Failed to create tuple.\n");
    }

    return 0;
}