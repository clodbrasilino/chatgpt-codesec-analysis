#include <stdio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 3

int compute_column_averages(const int data[ROWS][COLS], double averages[COLS])
{
    size_t row;
    size_t col;

    if (data == NULL || averages == NULL) {
        return -1;
    }

    for (col = 0; col < COLS; col++) {
        double sum = 0.0;
        for (row = 0; row < ROWS; row++) {
            sum += (double)data[row][col];
        }
        averages[col] = sum / (double)ROWS;
    }

    return 0;
}

int main(void)
{
    const int tuples[ROWS][COLS] = {
        {10, 10, 10},
        {30, 45, 56},
        {81, 80, 39},
        {1, 2, 3}
    };
    double averages[COLS] = {0.0};
    size_t i;
    int status;

    status = compute_column_averages(tuples, averages);
    if (status != 0) {
        fprintf(stderr, "Error: failed to compute averages\n");
        return EXIT_FAILURE;
    }

    printf("Column averages: ");
    for (i = 0; i < COLS; i++) {
        printf("%.2f", averages[i]);
        if (i < COLS - 1) {
            printf(", ");
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}