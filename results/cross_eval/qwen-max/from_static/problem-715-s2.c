#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int *values;
    size_t length;
} IntTuple;

IntTuple stringToTuple(const char *str) {
    IntTuple result = {NULL, 0};

    if (str == NULL || *str == '\0') {
        return result;
    }

    char *tempStr = strdup(str);
    if (tempStr == NULL) {
        return result;
    }

    char *token = strtok(tempStr, ", ");
    while (token != NULL) {
        char *endptr;
        long value = strtol(token, &endptr, 10);
        if (*endptr != '\0' || (value > INT_MAX || value < INT_MIN)) {
            free(tempStr);
            free(result.values);
            result.values = NULL;
            return result;
        }
        int newLength = result.length + 1;
        int *newValues = realloc(result.values, newLength * sizeof(int));
        if (newValues == NULL) {
            free(tempStr);
            free(result.values);
            result.values = NULL;
            return result;
        }
        result.values = newValues;
        result.values[result.length] = (int)value;
        result.length = newLength;
        token = strtok(NULL, ", ");
    }

    free(tempStr);
    return result;
}

void freeTuple(IntTuple *tuple) {
    if (tuple->values != NULL) {
        free(tuple->values);
        tuple->values = NULL;
    }
    tuple->length = 0;
}

int main() {
    const char *input = "1, 2, 3, 4, 5";
    IntTuple tuple = stringToTuple(input);

    for (size_t i = 0; i < tuple.length; ++i) {
        printf("%d ", tuple.values[i]);
    }
    printf("\n");

    freeTuple(&tuple);
    return 0;
}