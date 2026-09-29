#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **strings;
    int count;
} StringTuple;

StringTuple *create_string_tuple(char *str, const char *delimiter) {
    StringTuple *tuple = (StringTuple *)malloc(sizeof(StringTuple));
    if (!tuple) return NULL;

    tuple->count = 0;
    tuple->strings = NULL;

    char *token = strtok(str, delimiter);
    while (token) {
        tuple->count++;
        tuple->strings = (char **)realloc(tuple->strings, tuple->count * sizeof(char *));
        if (!tuple->strings) {
            free(tuple);
            return NULL;
        }
        tuple->strings[tuple->count - 1] = strdup(token);
        if (!tuple->strings[tuple->count - 1]) {
            for (int i = 0; i < tuple->count - 1; i++) {
                free(tuple->strings[i]);
            }
            free(tuple->strings);
            free(tuple);
            return NULL;
        }
        token = strtok(NULL, delimiter);
    }

    return tuple;
}

void free_string_tuple(StringTuple *tuple) {
    if (tuple) {
        for (int i = 0; i < tuple->count; i++) {
            free(tuple->strings[i]);
        }
        free(tuple->strings);
        free(tuple);
    }
}

int main() {
    char str[] = "apple,banana,orange";
    const char *delimiter = ",";

    StringTuple *tuple = create_string_tuple(str, delimiter);
    if (tuple) {
        for (int i = 0; i < tuple->count; i++) {
            printf("%s\n", tuple->strings[i]);
        }
        free_string_tuple(tuple);
    } else {
        fprintf(stderr, "Failed to create string tuple\n");
    }

    return 0;
}