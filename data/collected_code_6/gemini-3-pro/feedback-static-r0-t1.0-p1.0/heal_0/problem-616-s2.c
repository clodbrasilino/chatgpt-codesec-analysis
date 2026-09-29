#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

Tuple* create_tuple(size_t size) {
    if (size == 0) {
        return NULL;
    }
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (!t) {
        return NULL;
    }
    t->elements = (int*)malloc(size * sizeof(int));
    if (!t->elements) {
        free(t);
        return NULL;
    }
    t->size = size;
    return t;
}

void free_tuple(Tuple *t) {
    if (t) {
        free(t->elements);
        free(t);
    }
}

Tuple* modulo_tuples(const Tuple *t1, const Tuple *t2) {
    if (!t1 || !t2 || t1->size != t2->size) {
        return NULL;
    }

    Tuple *result = create_tuple(t1->size);
    if (!result) {
        return NULL;
    }

    for (size_t i = 0; i < t1->size; ++i) {
        if (t2->elements[i] == 0) {
            free_tuple(result);
            return NULL;
        }
        result->elements[i] = t1->elements[i] % t2->elements[i];
    }

    return result;
}

int main(void) {
    Tuple *t1 = create_tuple(3);
    if (!t1) {
        return EXIT_FAILURE;
    }
    t1->elements[0] = 10;
    t1->elements[1] = 20;
    t1->elements[2] = 30;

    Tuple *t2 = create_tuple(3);
    if (!t2) {
        free_tuple(t1);
        return EXIT_FAILURE;
    }
    t2->elements[0] = 3;
    t2->elements[1] = 7;
    t2->elements[2] = 4;

    Tuple *result = modulo_tuples(t1, t2);
    if (result) {
        for (size_t i = 0; i < result->size; ++i) {
            printf("%d ", result->elements[i]);
        }
        printf("\n");
        free_tuple(result);
    } else {
        printf("Error during modulo operation.\n");
    }

    free_tuple(t1);
    free_tuple(t2);

    return EXIT_SUCCESS;
}