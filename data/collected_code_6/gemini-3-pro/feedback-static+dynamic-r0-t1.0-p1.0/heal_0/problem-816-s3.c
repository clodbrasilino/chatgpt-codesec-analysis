#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    int id;
    double value;
    char *name;
} Tuple;

int clear_tuples(Tuple *tuples, size_t count) {
    if (tuples == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; i++) {
        tuples[i].id = 0;
        tuples[i].value = 0.0;
        
        if (tuples[i].name != NULL) {
            free(tuples[i].name);
            tuples[i].name = NULL;
        }
    }

    return 0;
}

int main(void) {
    size_t count = 2;
    Tuple *my_tuples = (Tuple *)calloc(count, sizeof(Tuple));
    
    if (my_tuples == NULL) {
        return EXIT_FAILURE;
    }

    my_tuples[0].id = 1;
    my_tuples[0].value = 3.14;
    my_tuples[0].name = strdup("Item1");
    if (my_tuples[0].name == NULL) {
        free(my_tuples);
        return EXIT_FAILURE;
    }

    my_tuples[1].id = 2;
    my_tuples[1].value = 2.71;
    my_tuples[1].name = strdup("Item2");
    if (my_tuples[1].name == NULL) {
        free(my_tuples[0].name);
        free(my_tuples);
        return EXIT_FAILURE;
    }

    if (clear_tuples(my_tuples, count) != 0) {
        free(my_tuples[0].name);
        free(my_tuples[1].name);
        free(my_tuples);
        return EXIT_FAILURE;
    }

    free(my_tuples);
    my_tuples = NULL;

    return EXIT_SUCCESS;
}