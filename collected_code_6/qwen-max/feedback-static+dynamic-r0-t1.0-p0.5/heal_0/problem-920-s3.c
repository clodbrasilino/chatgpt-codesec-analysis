#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* create_tuple(int a, int b) {
    Tuple *t = (Tuple *)malloc(sizeof(Tuple));
    t->a = a;
    t->b = b;
    return t;
}

void free_tuples(Tuple **tuples, int count) {
    for (int i = 0; i < count; ++i) {
        free(tuples[i]);
    }
    free(tuples);
}

int remove_none_tuples(Tuple **tuples, int *count) {
    int new_count = 0;
    for (int i = 0; i < *count; ++i) {
        if (tuples[i]->a != -1 || tuples[i]->b != -1) {
            tuples[new_count++] = tuples[i];
        } else {
            free(tuples[i]);
        }
    }
    *count = new_count;
    return new_count;
}

int main() {
    Tuple *tuples[] = {
        create_tuple(1, 2),
        create_tuple(-1, -1),
        create_tuple(3, 4),
        create_tuple(-1, -1),
        create_tuple(5, 6)
    };
    int count = sizeof(tuples) / sizeof(tuples[0]);

    count = remove_none_tuples(tuples, &count);

    for (int i = 0; i < count; ++i) {
        printf("(%d, %d)\n", tuples[i]->a, tuples[i]->b);
    }

    free_tuples(tuples, count);
    return 0;
}