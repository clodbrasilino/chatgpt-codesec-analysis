#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t count;
} Tuple;

/* Possible weaknesses found:
 *  Parameter 't' can be declared as pointer to const [constParameterPointer]
 */
bool check_tuple_k(Tuple *t, size_t k) {
    if (t == NULL) {
        return false;
    }
    if (t->elements == NULL && t->count == 0) {
        return k == 0;
    }
    if (t->elements == NULL && t->count > 0) {
        return false;
    }
    return t->count == k;
}

Tuple* create_tuple(size_t count) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->count = count;
    if (count > 0) {
        t->elements = (int *)malloc(count * sizeof(int));
        if (t->elements == NULL) {
            free(t);
            return NULL;
        }
        for (size_t i = 0; i < count; i++) {
            t->elements[i] = 0;
        }
    } else {
        t->elements = NULL;
    }
    return t;
}

void destroy_tuple(Tuple *t) {
    if (t != NULL) {
        free(t->elements);
        free(t);
    }
}

int main(void) {
    Tuple *t1 = create_tuple(5);
    Tuple *t2 = create_tuple(3);
    Tuple *t3 = create_tuple(0);

    if (t1 == NULL || t2 == NULL || t3 == NULL) {
        destroy_tuple(t1);
        destroy_tuple(t2);
        destroy_tuple(t3);
        return 1;
    }

    printf("%d\n", check_tuple_k(t1, 5));
    printf("%d\n", check_tuple_k(t2, 5));
    printf("%d\n", check_tuple_k(t3, 0));
    printf("%d\n", check_tuple_k(NULL, 0));

    destroy_tuple(t1);
    destroy_tuple(t2);
    destroy_tuple(t3);

    return 0;
}