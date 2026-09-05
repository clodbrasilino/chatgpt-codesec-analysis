#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t count;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleOfTuples;

double find_average(const TupleOfTuples *tuple_of_tuples)
{
    if (tuple_of_tuples == NULL || tuple_of_tuples->tuples == NULL || tuple_of_tuples->count == 0) {
        return 0.0;
    }

    double sum = 0.0;
    size_t total_count = 0;

    for (size_t i = 0; i < tuple_of_tuples->count; i++) {
        const Tuple *current_tuple = &tuple_of_tuples->tuples[i];

        if (current_tuple->values == NULL || current_tuple->count == 0) {
            continue;
        }

        for (size_t j = 0; j < current_tuple->count; j++) {
            sum += current_tuple->values[j];
            total_count++;
        }
    }

    if (total_count == 0) {
        return 0.0;
    }

    return sum / total_count;
}

int main(void)
{
    int tuple1_values[] = {1, 2, 3};
    int tuple2_values[] = {4, 5};
    int tuple3_values[] = {6, 7, 8, 9};

    Tuple tuples[] = {
        {tuple1_values, sizeof(tuple1_values) / sizeof(tuple1_values[0])},
        {tuple2_values, sizeof(tuple2_values) / sizeof(tuple2_values[0])},
        {tuple3_values, sizeof(tuple3_values) / sizeof(tuple3_values[0])}
    };

    TupleOfTuples tuple_of_tuples = {
        tuples,
        sizeof(tuples) / sizeof(tuples[0])
    };

    double average = find_average(&tuple_of_tuples);

    printf("Average: %.2f\n", average);

    return EXIT_SUCCESS;
}