#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    char b;
} tuple;

tuple* repeat_tuple(tuple given_tuple, size_t times) {
    tuple *repeated_tuples = malloc(times * sizeof(tuple));
    if(repeated_tuples == NULL) {
        return NULL;
    }

    for(size_t i = 0; i < times; i++) {
        repeated_tuples[i] = given_tuple;
    }

    return repeated_tuples;
}

int main() {
    tuple test_tuple = {4, 'a'};
    size_t times = 5;
    tuple *repeated_tuples = repeat_tuple(test_tuple, times);

    if(repeated_tuples == NULL) {
        printf("Failed to allocate memory.\n");
        return EXIT_FAILURE;
    }

    for(size_t i = 0; i < times; i++) {
        printf("tuple %lu: { %d, %c }\n", i, repeated_tuples[i].a, repeated_tuples[i].b);
    }

    free(repeated_tuples);

    return EXIT_SUCCESS;
}