#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} IntTuple;

IntTuple parse_int_tuple(const char *str) {
    IntTuple tuple = {NULL, 0};
    if (str == NULL || *str == '\0') return tuple;

    char *token;
    const char *delim = " ,";
    token = strtok((char *)str, delim);
    while (token != NULL) {
        tuple.length++;
        token = strtok(NULL, delim);
    }

    tuple.data = (int *)malloc(tuple.length * sizeof(int));
    if (tuple.data == NULL) {
        tuple.length = 0;
        return tuple;
    }

    token = strtok((char *)str, delim);
    for (size_t i = 0; i < tuple.length; i++) {
        tuple.data[i] = atoi(token);
        token = strtok(NULL, delim);
    }

    return tuple;
}

void free_int_tuple(IntTuple *tuple) {
    if (tuple->data != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->length = 0;
    }
}

int main() {
    const char *input = "1, 2, 3, 4, 5";
    IntTuple result = parse_int_tuple(input);

    for (size_t i = 0; i < result.length; i++) {
        printf("%d ", result.data[i]);
    }
    printf("\n");

    free_int_tuple(&result);
    return 0;
}