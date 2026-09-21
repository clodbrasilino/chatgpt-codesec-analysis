#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    double value;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[50];
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