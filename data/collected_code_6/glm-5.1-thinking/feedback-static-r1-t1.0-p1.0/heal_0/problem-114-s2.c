#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int freq;
} Tuple;

void assign_frequencies(Tuple *tuples, size_t count) {
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        tuples[i].freq = 0;
    }

    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < count; j++) {
            if (tuples[i].a == tuples[j].a && tuples[i].b == tuples[j].b) {
                tuples[i].freq++;
            }
        }
    }
}

int main(void) {
    size_t count = 6;
    Tuple *tuples = malloc(count * sizeof(Tuple));
    
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    tuples[0] = (Tuple){1, 2, 0};
    tuples[1] = (Tuple){3, 4, 0};
    tuples[2] = (Tuple){1, 2, 0};
    tuples[3] = (Tuple){5, 6, 0};
    tuples[4] = (Tuple){3, 4, 0};
    tuples[5] = (Tuple){1, 2, 0};

    assign_frequencies(tuples, count);

    for (size_t i = 0; i < count; i++) {
        printf("(%d, %d) freq: %d\n", tuples[i].a, tuples[i].b, tuples[i].freq);
    }

    free(tuples);
    return EXIT_SUCCESS;
}