#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* remove_matching_tuples(Tuple* t1, size_t* len1, Tuple* t2, size_t len2) {
    if (t1 == NULL || len1 == NULL || t2 == NULL) {
        return t1;
    }

    size_t current_len = *len1;
    size_t write_idx = 0;

    for (size_t i = 0; i < current_len; i++) {
        int match = 0;
        for (size_t j = 0; j < len2; j++) {
            if (t1[i].a == t2[j].a && t1[i].b == t2[j].b) {
                match = 1;
                break;
            }
        }

        if (!match) {
            if (write_idx != i) {
                t1[write_idx] = t1[i];
            }
            write_idx++;
        }
    }

    *len1 = write_idx;

    if (write_idx == 0) {
        free(t1);
        return NULL;
    }

    Tuple* resized = realloc(t1, write_idx * sizeof(Tuple));
    if (resized != NULL) {
        return resized;
    }

    return t1;
}

int main(void) {
    size_t len1 = 5;
    Tuple* t1 = malloc(len1 * sizeof(Tuple));
    if (t1 == NULL) {
        return EXIT_FAILURE;
    }

    t1[0].a = 1; t1[0].b = 2;
    t1[1].a = 3; t1[1].b = 4;
    t1[2].a = 5; t1[2].b = 6;
    t1[3].a = 7; t1[3].b = 8;
    t1[4].a = 9; t1[4].b = 10;

    size_t len2 = 3;
    Tuple t2[] = {{3, 4}, {7, 8}, {11, 12}};

    t1 = remove_matching_tuples(t1, &len1, t2, len2);

    for (size_t i = 0; i < len1; i++) {
        printf("(%d, %d)\n", t1[i].a, t1[i].b);
    }

    free(t1);

    return EXIT_SUCCESS;
}