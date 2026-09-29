#include <stdio.h>
#include <stdlib.h>

struct Tuple {
    int *elements;
    size_t size;
};

struct TupleOfTuples {
    struct Tuple *tuples;
    size_t size;
};

double calculate_average(const struct TupleOfTuples *tot) {
    if (tot == NULL || tot->size == 0) {
        return 0.0;
    }

    long long sum = 0;
    size_t count = 0;

    for (size_t i = 0; i < tot->size; i++) {
        if (tot->tuples[i].elements != NULL) {
            for (size_t j = 0; j < tot->tuples[i].size; j++) {
                sum += tot->tuples[i].elements[j];
                count++;
            }
        }
    }

    if (count == 0) {
        return 0.0;
    }

    return (double)sum / count;
}

void free_tuple_of_tuples(struct TupleOfTuples *tot) {
    if (tot != NULL) {
        if (tot->tuples != NULL) {
            for (size_t i = 0; i < tot->size; i++) {
                free(tot->tuples[i].elements);
            }
            free(tot->tuples);
        }
        tot->tuples = NULL;
        tot->size = 0;
    }
}

int main(void) {
    struct TupleOfTuples tot;
    tot.size = 2;
    tot.tuples = malloc(tot.size * sizeof(struct Tuple));
    if (tot.tuples == NULL) {
        return EXIT_FAILURE;
    }

    tot.tuples[0].size = 3;
    tot.tuples[0].elements = malloc(tot.tuples[0].size * sizeof(int));
    if (tot.tuples[0].elements == NULL) {
        free_tuple_of_tuples(&tot);
        return EXIT_FAILURE;
    }
    tot.tuples[0].elements[0] = 1;
    tot.tuples[0].elements[1] = 2;
    tot.tuples[0].elements[2] = 3;

    tot.tuples[1].size = 2;
    tot.tuples[1].elements = malloc(tot.tuples[1].size * sizeof(int));
    if (tot.tuples[1].elements == NULL) {
        free_tuple_of_tuples(&tot);
        return EXIT_FAILURE;
    }
    tot.tuples[1].elements[0] = 4;
    tot.tuples[1].elements[1] = 5;

    double average = calculate_average(&tot);
    printf("Average: %.2f\n", average);

    free_tuple_of_tuples(&tot);

    return EXIT_SUCCESS;
}