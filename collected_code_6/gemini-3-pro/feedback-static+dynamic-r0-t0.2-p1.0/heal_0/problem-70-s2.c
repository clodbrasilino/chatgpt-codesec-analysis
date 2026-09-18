#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int* elements;
    size_t length;
} Tuple;

bool check_equal_lengths(Tuple* tuples, size_t num_tuples) {
    if (tuples == NULL || num_tuples == 0) {
        return false;
    }

    size_t first_length = tuples[0].length;

    for (size_t i = 1; i < num_tuples; ++i) {
        if (tuples[i].length != first_length) {
            return false;
        }
    }

    return true;
}

int main() {
    Tuple tuples[3];
    
    tuples[0].length = 3;
    tuples[0].elements = (int*)malloc(tuples[0].length * sizeof(int));
    if (tuples[0].elements == NULL) return 1;

    tuples[1].length = 3;
    tuples[1].elements = (int*)malloc(tuples[1].length * sizeof(int));
    if (tuples[1].elements == NULL) {
        free(tuples[0].elements);
        return 1;
    }

    tuples[2].length = 3;
    tuples[2].elements = (int*)malloc(tuples[2].length * sizeof(int));
    if (tuples[2].elements == NULL) {
        free(tuples[0].elements);
        free(tuples[1].elements);
        return 1;
    }

    bool result = check_equal_lengths(tuples, 3);
    
    if (result) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Tuples do not have equal length.\n");
    }

    free(tuples[0].elements);
    free(tuples[1].elements);
    free(tuples[2].elements);

    return 0;
}