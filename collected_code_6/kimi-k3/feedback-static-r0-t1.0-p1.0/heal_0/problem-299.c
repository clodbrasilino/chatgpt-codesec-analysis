#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t count;
} Tuple;

int calculate_max_aggregate(const Tuple *tuples, size_t tuple_count, int *result)
{
    if (tuples == NULL || result == NULL || tuple_count == 0) {
        return -1;
    }

    int max_sum = 0;
    int first_valid = 1;

    for (size_t i = 0; i < tuple_count; i++) {
        if (tuples[i].values == NULL || tuples[i].count == 0) {
            continue;
        }

        int sum = 0;
        for (size_t j = 0; j < tuples[i].count; j++) {
            sum += tuples[i].values[j];
        }

        if (first_valid || sum > max_sum) {
            max_sum = sum;
            first_valid = 0;
        }
    }

    if (first_valid) {
        return -1;
    }

    *result = max_sum;
    return 0;
}

int main(void)
{
    int data1[] = {1, 2, 3};
    int data2[] = {10, 20};
    int data3[] = {5, 5, 5, 5};
    int data4[] = {-1, -2, -3};

    Tuple tuples[] = {
        {data1, sizeof(data1) / sizeof(data1[0])},
        {data2, sizeof(data2) / sizeof(data2[0])},
        {data3, sizeof(data3) / sizeof(data3[0])},
        {data4, sizeof(data4) / sizeof(data4[0])}
    };

    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    int max_aggregate = 0;

    if (calculate_max_aggregate(tuples, tuple_count, &max_aggregate) == 0) {
        printf("Maximum aggregate: %d\n", max_aggregate);
    } else {
        fprintf(stderr, "Error: Invalid input or no valid tuples\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}