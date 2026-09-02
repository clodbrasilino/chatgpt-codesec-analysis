#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} IntTuple;

IntTuple parse_int_tuple(const char *str) {
    if (str == NULL || *str == '\0') return (IntTuple){NULL, 0};

    char *cpy = strdup(str);
    if (cpy == NULL) return (IntTuple){NULL, 0};

    IntTuple tuple = {NULL, 0};
    char *token = strtok(cpy, " ,");
    while (token != NULL) {
        tuple.length++;
        token = strtok(NULL, " ,");
    }

    tuple.data = (int *)malloc(tuple.length * sizeof(int));
    if (tuple.data == NULL) {
        free(cpy);
        return (IntTuple){NULL, 0};
    }

    token = strtok(cpy, " ,");
    for (size_t i = 0; i < tuple.length && token != NULL; i++) {
        tuple.data[i] = atoi(token);
        token = strtok(NULL, " ,");
    }

    free(cpy);
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