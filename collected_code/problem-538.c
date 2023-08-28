#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int size;
} Tuple;

Tuple convertStringListToTuple(char **stringList, int size) {
    Tuple tuple;
    tuple.data = (char **)malloc(size * sizeof(char *));
    tuple.size = size;

    for (int i = 0; i < size; i++) {
        tuple.data[i] = (char *)malloc((strlen(stringList[i]) + 1) * sizeof(char));
        strcpy(tuple.data[i], stringList[i]);
    }

    return tuple;
}

int main() {
    char *stringList[] = {"Hello", "World", "Example"};
    int size = sizeof(stringList) / sizeof(stringList[0]);

    Tuple tuple = convertStringListToTuple(stringList, size);

    for (int i = 0; i < tuple.size; i++) {
        printf("%d: %s\n", i, tuple.data[i]);
    }

    for (int i = 0; i < tuple.size; i++) {
        free(tuple.data[i]);
    }
    free(tuple.data);

    return 0;
}