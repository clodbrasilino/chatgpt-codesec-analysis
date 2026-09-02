#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *values;
    size_t count;
} IntTuple;

IntTuple parse_integers(const char *str) {
    IntTuple tuple = {0};
    const char *delim = " ,";
    char *token;
    char *temp_str = strdup(str);
    if (temp_str == NULL) {
        return tuple;
    }

    token = strtok(temp_str, delim);
    while (token != NULL) {
        int value = (int)strtol(token, NULL, 10);
        tuple.values = realloc(tuple.values, (tuple.count + 1) * sizeof(int));
        if (tuple.values == NULL) {
            free(temp_str);
            return tuple;
        }
        tuple.values[tuple.count++] = value;
        token = strtok(NULL, delim);
    }
    free(temp_str);
    return tuple;
}

void free_tuple(IntTuple *tuple) {
    if (tuple->values != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->count = 0;
    }
}

int main() {
    const char *input = "1, 2, 3, 4, 5";
    IntTuple tuple = parse_integers(input);

    for (size_t i = 0; i < tuple.count; ++i) {
        printf("%d ", tuple.values[i]);
    }
    printf("\n");

    free_tuple(&tuple);
    return 0;
}