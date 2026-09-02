#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} IntTuple;

IntTuple parse_int_tuple(const char *input) {
    IntTuple result = {NULL, 0};
    if (input == NULL) return result;

    char *str = strdup(input);
    if (str == NULL) return result;

    char *token = strtok(str, ",");
    if (token == NULL) {
        free(str);
        return result;
    }

    result.data = (int *)malloc(sizeof(int));
    if (result.data == NULL) {
        free(str);
        return result;
    }

    result.length = 1;
    result.data[0] = atoi(token);

    while ((token = strtok(NULL, ",")) != NULL) {
        result.length++;
        result.data = (int *)realloc(result.data, result.length * sizeof(int));
        if (result.data == NULL) {
            free(str);
            return result;
        }
        result.data[result.length - 1] = atoi(token);
    }

    free(str);
    return result;
}

void free_int_tuple(IntTuple *tuple) {
    if (tuple->data != NULL) {
        free(tuple->data);
        tuple->data = NULL;
    }
    tuple->length = 0;
}

int main() {
    const char *input = "1,2,3,4,5";
    IntTuple tuple = parse_int_tuple(input);

    for (size_t i = 0; i < tuple.length; ++i) {
        printf("%d ", tuple.data[i]);
    }
    printf("\n");

    free_int_tuple(&tuple);
    return 0;
}