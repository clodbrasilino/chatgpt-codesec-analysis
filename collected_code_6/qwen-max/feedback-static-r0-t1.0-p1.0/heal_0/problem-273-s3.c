#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int z;
} Tuple;

Tuple subtract_tuples(const Tuple *t1, const Tuple *t2) {
    if (t1 == NULL || t2 == NULL) {
        fprintf(stderr, "Error: Input tuples are null\n");
        exit(EXIT_FAILURE);
    }
    Tuple result = {t1->x - t2->x, t1->y - t2->y, t1->z - t2->z};
    return result;
}

int main() {
    Tuple t1 = {5, 6, 7};
    Tuple t2 = {1, 2, 3};
    Tuple result = subtract_tuples(&t1, &t2);

    printf("Result: (%d, %d, %d)\n", result.x, result.y, result.z);
    return 0;
}