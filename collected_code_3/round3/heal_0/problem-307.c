#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Tuple;

char* getColonOfTuple(Tuple tuple) {
    char* result = (char*) malloc(20 * sizeof(char));
    sprintf(result, "%d:%d", tuple.first, tuple.second);
    return result;
}

int main() {
    Tuple tuple;
    tuple.first = 5;
    tuple.second = 10;
    char* result = getColonOfTuple(tuple);
    printf("%s\n", result);
    free(result);
    return 0;
}