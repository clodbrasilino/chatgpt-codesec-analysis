#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

bool tuple_init(Tuple *t, size_t size) {
    if (t == NULL) {
        return false;
    }
    t->size = size;
    if (size == 0) {
        t->data = NULL;
        return true;
    }
    t->data = malloc(size * sizeof(int));
    if (t->data == NULL) {
        t->size = 0;
        return false;
    }
    return true;
}

void tuple_free(Tuple *t) {
    if (t != NULL) {
        free(t->data);
        t->data = NULL;
        t->size = 0;
    }
}

bool tuple_is_subset(const Tuple *subset, const Tuple *superset) {
    if (subset == NULL || superset == NULL) {
        return false;
    }
    if (subset->size == 0) {
        return true;
    }
    if (subset->size > superset->size) {
        return false;
    }
    if (subset->data == NULL || superset->data == NULL) {
        return false;
    }

    for (size_t i = 0; i < subset->size; i++) {
        bool found = false;
        for (size_t j = 0; j < superset->size; j++) {
            if (subset->data[i] == superset->data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

int main(void) {
    Tuple t1 = {0};
    Tuple t2 = {0};
    int result = EXIT_FAILURE;

    if (!tuple_init(&t1, 3)) {
        fprintf(stderr, "Failed to initialize tuple 1\n");
        goto cleanup;
    }
    if (!tuple_init(&t2, 5)) {
        fprintf(stderr, "Failed to initialize tuple 2\n");
        goto cleanup;
    }

    t1.data[0] = 1;
    t1.data[1] = 2;
    t1.data[2] = 3;

    t2.data[0] = 5;
    t2.data[1] = 1;
    t2.data[2] = 4;
    t2.data[3] = 2;
    t2.data[4] = 3;

    if (tuple_is_subset(&t1, &t2)) {
        printf("Tuple 1 is a subset of Tuple 2\n");
    } else {
        printf("Tuple 1 is not a subset of Tuple 2\n");
    }

    result = EXIT_SUCCESS;

cleanup:
    tuple_free(&t1);
    tuple_free(&t2);
    return result;
}