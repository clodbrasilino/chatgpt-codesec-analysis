#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Tuple;

static bool tuple_equal(Tuple a, Tuple b) {
    return a.x == b.x && a.y == b.y;
}

int remove_matching_tuples(Tuple *a, size_t *na, Tuple *b, size_t *nb) {
    bool *remove_a = NULL;
    bool *remove_b = NULL;
    size_t i;
    size_t j;
    size_t write;

    if (na == NULL || nb == NULL) {
        return -1;
    }
    if (*na == 0 || *nb == 0) {
        return 0;
    }
    if (a == NULL || b == NULL) {
        return -1;
    }

    remove_a = calloc(*na, sizeof(*remove_a));
    if (remove_a == NULL) {
        return -1;
    }

    remove_b = calloc(*nb, sizeof(*remove_b));
    if (remove_b == NULL) {
        free(remove_a);
        return -1;
    }

    for (i = 0; i < *na; ++i) {
        for (j = 0; j < *nb; ++j) {
            if (tuple_equal(a[i], b[j])) {
                remove_a[i] = true;
                remove_b[j] = true;
            }
        }
    }

    write = 0;
    for (i = 0; i < *na; ++i) {
        if (!remove_a[i]) {
            a[write++] = a[i];
        }
    }
    *na = write;

    write = 0;
    for (j = 0; j < *nb; ++j) {
        if (!remove_b[j]) {
            b[write++] = b[j];
        }
    }
    *nb = write;

    free(remove_a);
    free(remove_b);
    return 0;
}

int main(void) {
    Tuple a[] = { {1, 2}, {3, 4}, {5, 6}, {7, 8} };
    Tuple b[] = { {3, 4}, {7, 8}, {9, 10} };
    size_t na = sizeof(a) / sizeof(a[0]);
    size_t nb = sizeof(b) / sizeof(b[0]);
    size_t i;

    if (remove_matching_tuples(a, &na, b, &nb) != 0) {
        return 1;
    }

    for (i = 0; i < na; ++i) {
        printf("(%d,%d) ", a[i].x, a[i].y);
    }
    printf("\n");

    for (i = 0; i < nb; ++i) {
        printf("(%d,%d) ", b[i].x, b[i].y);
    }
    printf("\n");

    return 0;
}