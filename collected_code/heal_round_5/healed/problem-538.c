#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int size;
} Tuple;

Tuple convertStringListToTuple(char **stringList, int size) {
    Tuple tuple;
    tuple.data = (char **)calloc(size, sizeof(char *));
    tuple.size = size;

    if (tuple.data == NULL) {
        tuple.size = 0;
        return tuple;
    }

    for (int i = 0; i < size; i++) {
        if (stringList[i] != NULL) {
            size_t len = strnlen(stringList[i], size);
            tuple.data[i] = (char *)calloc(len + 1, sizeof(char));

            if (tuple.data[i] != NULL) {
                memmove(tuple.data[i], stringList[i], len);
                tuple.data[i][len] = '\0';
            }
        } else {
            tuple.data[i] = NULL;
        }
    }

    return tuple;
}

int main() {
    char *stringList[] = {"Hello", "World", "Example"};
    int size = sizeof(stringList) / sizeof(char *);
    Tuple tuple = convertStringListToTuple(stringList, size);

    for (int i = 0; i < tuple.size; i++) {
        if (tuple.data[i] != NULL) {
            printf("%d: %s\n", i, tuple.data[i]);
        }
    }
    for (int i = 0; i < tuple.size; i++) {
        free(tuple.data[i]);
    }
    free(tuple.data);

    return 0;
}