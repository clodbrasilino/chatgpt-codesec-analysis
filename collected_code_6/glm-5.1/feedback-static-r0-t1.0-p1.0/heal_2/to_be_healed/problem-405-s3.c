#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

bool tuple_contains(const Tuple *t, int target) {
    if (t == NULL || t->elements == NULL) {
        return false;
    }
    for (size_t i = 0; i < t->size; i++) {
        if (t->elements[i] == target) {
            return true;
        }
    }
    return false;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        t->elements = NULL;
        t->size = 0;
    }
}

int main(void) {
    Tuple t;
    t.size = 5;
    t.elements = (int *)malloc(t.size * sizeof(int));
    if (t.elements == NULL) {
        return EXIT_FAILURE;
    }

    t.elements[0] = 10;
    t.elements[1] = 20;
    t.elements[2] = 30;
    t.elements[3] = 40;
    t.elements[4] = 50;

    if (tuple_contains(&t, 30)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    if (tuple_contains(&t, 99)) {
        printf("Found\n");
    } else {
        printf("Not Found\n");
    }

    /* Possible weaknesses found:
     *  Condition '!tuple_contains(NULL,10)' is always true
     *  Calling function 'tuple_contains' returns 0
     *  Condition '!tuple_contains(NULL,10)' is always true [knownConditionTrueFalse]
     */
    if (!tuple_contains(NULL, 10)) {
        printf("Not Found\n");
    }

    tuple_free(&t);

    return EXIT_SUCCESS;
}