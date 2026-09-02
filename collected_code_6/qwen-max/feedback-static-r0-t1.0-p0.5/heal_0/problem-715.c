#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    size_t length;
} IntTuple;

IntTuple stringToIntTuple(const char *str) {
    IntTuple result = {NULL, 0};
    const char *p = str;
    int *tempArray = NULL;
    size_t tempLength = 0;
    size_t capacity = 10;

    tempArray = (int *)malloc(capacity * sizeof(int));
    if (tempArray == NULL) {
        return result;
    }

    while (*p) {
        char *endptr;
        long value = strtol(p, &endptr, 10);
        if (p == endptr) {
            free(tempArray);
            return result;
        }
        p = endptr;

        if (tempLength >= capacity) {
            capacity *= 2;
            int *newArray = (int *)realloc(tempArray, capacity * sizeof(int));
            if (newArray == NULL) {
                free(tempArray);
                return result;
            }
            tempArray = newArray;
        }
        tempArray[tempLength++] = (int)value;

        if (*p == ',') {
            p++;
        }
    }

    result.data = (int *)malloc(tempLength * sizeof(int));
    if (result.data == NULL) {
        free(tempArray);
        return result;
    }
    memcpy(result.data, tempArray, tempLength * sizeof(int));
    result.length = tempLength;
    free(tempArray);
    return result;
}

void printIntTuple(IntTuple tuple) {
    for (size_t i = 0; i < tuple.length; ++i) {
        printf("%d", tuple.data[i]);
        if (i < tuple.length - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void freeIntTuple(IntTuple tuple) {
    free(tuple.data);
}

int main() {
    const char *input = "1,2,3,4,5";
    IntTuple tuple = stringToIntTuple(input);
    if (tuple.data != NULL) {
        printIntTuple(tuple);
        freeIntTuple(tuple);
    } else {
        printf("Failed to convert string to tuple.\n");
    }
    return 0;
}