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

double calculate_average(const struct TupleOfTuples *tot, int *error) {
    if (tot == NULL || error == NULL) {
        if (error != NULL) {
            *error = 1;
        }
        return 0.0;
    }

    long long sum = 0;
    size_t count = 0;

    for (size_t i = 0; i < tot->size; i++) {
        if (tot->tuples[i].elements == NULL) {
            *error = 1;
            return 0.0;
        }
        for (size_t j = 0; j < tot->tuples[i].size; j++) {
            sum += tot->tuples[i].elements[j];
            count++;
        }
    }

    if (count == 0) {
        *error = 1;
        return 0.0;
    }

    *error = 0;
    return (double)sum / (double)count;
}

int main(void) {
    int t1_data[] = {1, 2, 3};
    int t2_data[] = {4, 5};
    int t3_data[] = {6, 7, 8, 9};

    struct Tuple t1 = {t1_data, 3};
    struct Tuple t2 = {t2_data, 2};
    struct Tuple t3 = {t3_data, 4};

    struct Tuple tuples_array[] = {t1, t2, t3};
    struct TupleOfTuples tot = {tuples_array, 3};

    int error = 0;
    double average = calculate_average(&tot, &error);

    if (error == 0) {
        printf("Average: %f\n", average);
    } else {
        printf("Error calculating average.\n");
    }

    return 0;
}