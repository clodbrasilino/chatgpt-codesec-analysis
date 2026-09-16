#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUES 10

typedef struct {
    int values[MAX_VALUES];
    size_t count;
} Tuple;

long cumulative_sum(const Tuple *tuples, size_t num_tuples)
{
    long total = 0;
    size_t i;
    size_t j;

    if (tuples == NULL) {
        return 0;
    }

    for (i = 0; i < num_tuples; i++) {
        for (j = 0; j < tuples[i].count && j < MAX_VALUES; j++) {
            total += (long)tuples[i].values[j];
        }
    }

    return total;
}

int main(void)
{
    Tuple tuple_list[3];
    long result;

    tuple_list[0].values[0] = 1;
    tuple_list[0].values[1] = 3;
    tuple_list[0].count = 2;

    tuple_list[1].values[0] = 5;
    tuple_list[1].values[1] = 6;
    tuple_list[1].values[2] = 7;
    tuple_list[1].count = 3;

    tuple_list[2].values[0] = 2;
    tuple_list[2].values[1] = 6;
    tuple_list[2].count = 2;

    result = cumulative_sum(tuple_list, 3);

    if (printf("Cumulative sum: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}