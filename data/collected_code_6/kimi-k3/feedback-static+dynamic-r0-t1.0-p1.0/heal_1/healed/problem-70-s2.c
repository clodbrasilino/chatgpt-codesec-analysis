#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t length;
} Tuple;

int all_tuples_equal_length(const Tuple *tuples, size_t count) {
    size_t i;
    size_t expected_length;

    if (tuples == NULL || count == 0) {
        return 0;
    }

    expected_length = tuples[0].length;

    for (i = 1; i < count; i++) {
        if (tuples[i].length != expected_length) {
            return 0;
        }
    }

    return 1;
}

void free_tuples(Tuple *tuples, size_t count) {
    size_t i;
    if (tuples == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(tuples[i].elements);
    }
    free(tuples);
}

int main(void) {
    Tuple *equal_tuples;
    Tuple *unequal_tuples;
    size_t equal_count = 3;
    size_t unequal_count = 3;
    size_t i;

    equal_tuples = malloc(equal_count * sizeof(Tuple));
    if (equal_tuples == NULL) {
        return 1;
    }

    unequal_tuples = malloc(unequal_count * sizeof(Tuple));
    if (unequal_tuples == NULL) {
        free(equal_tuples);
        return 1;
    }

    for (i = 0; i < equal_count; i++) {
        equal_tuples[i].elements = malloc(3 * sizeof(int));
        if (equal_tuples[i].elements == NULL) {
            free_tuples(equal_tuples, i);
            free_tuples(unequal_tuples, 0);
            return 1;
        }
        equal_tuples[i].length = 3;
    }

    equal_tuples[0].elements[0] = 1;
    equal_tuples[0].elements[1] = 2;
    equal_tuples[0].elements[2] = 3;

    equal_tuples[1].elements[0] = 4;
    equal_tuples[1].elements[1] = 5;
    equal_tuples[1].elements[2] = 6;

    equal_tuples[2].elements[0] = 7;
    equal_tuples[2].elements[1] = 8;
    equal_tuples[2].elements[2] = 9;

    unequal_tuples[0].elements = malloc(3 * sizeof(int));
    if (unequal_tuples[0].elements == NULL) {
        free_tuples(equal_tuples, equal_count);
        free_tuples(unequal_tuples, 0);
        return 1;
    }
    unequal_tuples[0].length = 3;
    unequal_tuples[0].elements[0] = 1;
    unequal_tuples[0].elements[1] = 2;
    unequal_tuples[0].elements[2] = 3;

    unequal_tuples[1].elements = malloc(2 * sizeof(int));
    if (unequal_tuples[1].elements == NULL) {
        free_tuples(equal_tuples, equal_count);
        free_tuples(unequal_tuples, 1);
        return 1;
    }
    unequal_tuples[1].length = 2;
    unequal_tuples[1].elements[0] = 10;
    unequal_tuples[1].elements[1] = 11;

    unequal_tuples[2].elements = malloc(3 * sizeof(int));
    if (unequal_tuples[2].elements == NULL) {
        free_tuples(equal_tuples, equal_count);
        free_tuples(unequal_tuples, 2);
        return 1;
    }
    unequal_tuples[2].length = 3;
    unequal_tuples[2].elements[0] = 7;
    unequal_tuples[2].elements[1] = 8;
    unequal_tuples[2].elements[2] = 9;

    if (all_tuples_equal_length(equal_tuples, equal_count)) {
        printf("All tuples in first set have equal length.\n");
    } else {
        printf("Tuples in first set have different lengths.\n");
    }

    if (all_tuples_equal_length(unequal_tuples, unequal_count)) {
        printf("All tuples in second set have equal length.\n");
    } else {
        printf("Tuples in second set have different lengths.\n");
    }

    free_tuples(equal_tuples, equal_count);
    free_tuples(unequal_tuples, unequal_count);

    return 0;
}