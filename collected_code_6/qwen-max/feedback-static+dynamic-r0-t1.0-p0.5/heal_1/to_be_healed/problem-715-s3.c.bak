#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} IntTuple;

IntTuple stringToIntTuple(const char *str) {
    IntTuple result = {NULL, 0};
    if (str == NULL || *str == '\0') return result;

    /* Possible weaknesses found:
     * ASan: BUS
     */
    char *token = strtok((char *)str, " ");
    if (token == NULL) return result;

    result.data = (int *)malloc(sizeof(int));
    if (result.data == NULL) return result;

    result.length = 1;
    result.data[0] = atoi(token);

    while ((token = strtok(NULL, " ")) != NULL) {
        result.length++;
        result.data = (int *)realloc(result.data, result.length * sizeof(int));
        if (result.data == NULL) {
            free(result.data);
            result.data = NULL;
            result.length = 0;
            return result;
        }
        result.data[result.length - 1] = atoi(token);
    }

    return result;
}

void freeIntTuple(IntTuple *tuple) {
    if (tuple->data != NULL) {
        free(tuple->data);
        tuple->data = NULL;
        tuple->length = 0;
    }
}

int main() {
    const char *input = "1 2 3 4 5";
    IntTuple tuple = stringToIntTuple(input);

    for (size_t i = 0; i < tuple.length; ++i) {
        printf("%d ", tuple.data[i]);
    }
    printf("\n");

    freeIntTuple(&tuple);
    return 0;
}