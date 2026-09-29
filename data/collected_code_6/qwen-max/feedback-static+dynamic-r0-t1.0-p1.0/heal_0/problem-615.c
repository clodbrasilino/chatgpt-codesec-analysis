#include <stdio.h>
#include <stddef.h>

double average_of_tuples(const double *data, size_t num_items) {
    if (num_items == 0) return 0.0;

    double total = 0.0;
    for (size_t i = 0; i < num_items; ++i) {
        total += data[i];
    }

    return total / num_items;
}

int main() {
    const double tuples[][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    size_t num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    size_t tuple_size = sizeof(tuples[0]) / sizeof(tuples[0][0]);

    double averages[num_tuples] = {0.0};

    for (size_t i = 0; i < num_tuples; ++i) {
        averages[i] = average_of_tuples(tuples[i], tuple_size);
    }

    for (size_t i = 0; i < num_tuples; ++i) {
        printf("Average of tuple %zu: %.2f\n", i + 1, averages[i]);
    }

    return 0;
}