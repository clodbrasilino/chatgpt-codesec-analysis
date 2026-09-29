#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} IntTuple;

IntTuple parseStringToIntTuple(const char *str) {
    IntTuple result = {NULL, 0};
    if (str == NULL) return result;

    char *tempStr = strdup(str);
    if (tempStr == NULL) return result;

    char *token = strtok(tempStr, " ,");
    while (token != NULL) {
        result.length++;
        token = strtok(NULL, " ,");
    }

    result.data = (int *)malloc(result.length * sizeof(int));
    if (result.data == NULL) {
        free(tempStr);
        return result;
    }

    token = strtok(tempStr, " ,");
    for (size_t i = 0; i < result.length; i++) {
        result.data[i] = (token ? atoi(token) : 0);
        token = strtok(NULL, " ,");
    }

    free(tempStr);
    return result;
}

void freeIntTuple(IntTuple *tuple) {
    if (tuple->data != NULL) {
        free(tuple->data);
        tuple->data = NULL;
    }
    tuple->length = 0;
}

int main() {
    const char *input = "1, 2, 3, 4, 5";
    IntTuple tuple = parseStringToIntTuple(input);

    for (size_t i = 0; i < tuple.length; i++) {
        printf("%d ", tuple.data[i]);
    }
    printf("\n");

    freeIntTuple(&tuple);
    return 0;
}