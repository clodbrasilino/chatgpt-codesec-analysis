#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t length;
} IntTuple;

IntTuple stringToIntTuple(const char *str) {
    IntTuple result = {NULL, 0};
    if (str == NULL || *str == '\0') return result;

    char *s = strdup(str);
    if (s == NULL) return result;

    char *token = strtok(s, " ");
    if (token == NULL) {
        free(s);
        return result;
    }

    result.data = (int *)malloc(sizeof(int));
    if (result.data == NULL) {
        free(s);
        return result;
    }

    long num = strtol(token, NULL, 10);
    if (num < INT_MIN || num > INT_MAX) {
        free(s);
        free(result.data);
        return result;
    }
    result.data[0] = (int)num;
    result.length = 1;

    while ((token = strtok(NULL, " ")) != NULL) {
        result.length++;
        void *tmp = realloc(result.data, result.length * sizeof(int));
        if (tmp == NULL) {
            free(s);
            free(result.data);
            result.data = NULL;
            result.length = 0;
            return result;
        }
        result.data = (int *)tmp;

        num = strtol(token, NULL, 10);
        if (num < INT_MIN || num > INT_MAX) {
            free(s);
            free(result.data);
            result.data = NULL;
            result.length = 0;
            return result;
        }
        result.data[result.length - 1] = (int)num;
    }
    free(s);
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