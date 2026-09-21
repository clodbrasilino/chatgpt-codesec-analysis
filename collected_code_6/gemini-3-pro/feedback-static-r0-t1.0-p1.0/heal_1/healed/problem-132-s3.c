#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
    const char* name;
} Tuple;

char* tupleToString(const Tuple* t) {
    if (t == NULL) {
        return NULL;
    }

    size_t size = snprintf(NULL, 0, "(%d, %f, '%s')", t->id, t->value, t->name) + 1;
    char* str = (char*)malloc(size);
    if (str == NULL) {
        return NULL;
    }

    snprintf(str, size, "(%d, %f, '%s')", t->id, t->value, t->name);
    return str;
}

int main(void) {
    Tuple myTuple = {1, 3.14159, "Example"};

    char* result = tupleToString(&myTuple);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}