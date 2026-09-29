#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

void find_combinations_of_sums(Tuple* tuples, int size) {
    if (tuples == NULL || size <= 0) {
        return;
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            int sum_x = tuples[i].x + tuples[j].x;
            int sum_y = tuples[i].y + tuples[j].y;
            printf("Sum of tuple %d and tuple %d: (%d, %d)\n", i, j, sum_x, sum_y);
        }
    }
}

int main(void) {
    int size = 4;
    Tuple* tuples = (Tuple*)malloc(size * sizeof(Tuple));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    tuples[0].x = 1;
    tuples[0].y = 2;
    tuples[1].x = 3;
    tuples[1].y = 4;
    tuples[2].x = 5;
    tuples[2].y = 6;
    tuples[3].x = 7;
    tuples[3].y = 8;

    find_combinations_of_sums(tuples, size);

    free(tuples);
    tuples = NULL;

    return EXIT_SUCCESS;
}