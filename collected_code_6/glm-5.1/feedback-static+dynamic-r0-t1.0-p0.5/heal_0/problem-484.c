#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* remove_matching_tuples(Tuple* t1, size_t* s1, Tuple* t2, size_t* s2) {
    Tuple* res1 = malloc(*s1 * sizeof(Tuple));
    Tuple* res2 = malloc(*s2 * sizeof(Tuple));
    if (!res1 || !res2) {
        free(res1);
        free(res2);
        return NULL;
    }

    size_t r1 = 0;
    size_t r2 = 0;

    for (size_t i = 0; i < *s1; i++) {
        int match = 0;
        for (size_t j = 0; j < *s2; j++) {
            if (t1[i].a == t2[j].a && t1[i].b == t2[j].b) {
                match = 1;
                break;
            }
        }
        if (!match) {
            res1[r1++] = t1[i];
        }
    }

    for (size_t i = 0; i < *s2; i++) {
        int match = 0;
        for (size_t j = 0; j < *s1; j++) {
            if (t2[i].a == t1[j].a && t2[i].b == t1[j].b) {
                match = 1;
                break;
            }
        }
        if (!match) {
            res2[r2++] = t2[i];
        }
    }

    memcpy(t1, res1, r1 * sizeof(Tuple));
    memcpy(t2, res2, r2 * sizeof(Tuple));
    *s1 = r1;
    *s2 = r2;

    free(res1);
    free(res2);

    return t1;
}

int main() {
    Tuple t1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple t2[] = {{3, 4}, {7, 8}, {1, 2}};
    size_t s1 = sizeof(t1) / sizeof(t1[0]);
    size_t s2 = sizeof(t2) / sizeof(t2[0]);

    remove_matching_tuples(t1, &s1, t2, &s2);

    for (size_t i = 0; i < s1; i++) {
        printf("(%d, %d) ", t1[i].a, t1[i].b);
    }
    printf("\n");

    for (size_t i = 0; i < s2; i++) {
        printf("(%d, %d) ", t2[i].a, t2[i].b);
    }
    printf("\n");

    return 0;
}