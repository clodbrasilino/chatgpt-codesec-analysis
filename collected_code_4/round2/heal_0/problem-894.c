#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float x;
    float y;
} Tuple;

Tuple* stringToTuple(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    float x, y;
    if (sscanf(str, "{%f,%f}", &x, &y) != 2) {
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->x = x;
    tuple->y = y;
    return tuple;
}

void freeTuple(Tuple* tuple) {
    if (tuple != NULL) {
        free(tuple);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Give a string to convert to a tuple\n");
        return 1;
    }
    Tuple *tuple = stringToTuple(argv[1]);

    if (tuple == NULL) {
        printf("Couldn't convert string to tuple\n");
        return 1;
    }

    printf("Tuple: {%.2f, %.2f}\n", tuple->x, tuple->y);
    freeTuple(tuple);
    return 0;
}