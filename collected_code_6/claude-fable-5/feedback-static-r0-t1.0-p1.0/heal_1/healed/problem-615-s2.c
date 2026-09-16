#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 4

static int compute_averages(const double data[ROWS][COLS], size_t rows, size_t cols, double *result, size_t result_len)
{
    size_t i;
    size_t j;

    if (data == NULL || result == NULL) {
        return -1;
    }
    if (rows == 0 || cols == 0 || result_len < cols) {
        return -1;
    }

    for (j = 0; j < cols; j++) {
        double sum = 0.0;
        for (i = 0; i < rows; i++) {
            sum += data[i][j];
        }
        result[j] = sum / (double)rows;
    }

    return 0;
}

int main(void)
{
    const double tuples[ROWS][COLS] = {
        {10.0, 10.0, 10.0, 12.0},
        {30.0, 45.0, 56.0, 45.0},
        {81.0, 80.0, 39.0, 32.0}
    };
    double averages[COLS];
    size_t j;
    int status;

    status = compute_averages(tuples, ROWS, COLS, averages, COLS);
    if (status != 0) {
        fprintf(stderr, "Error: failed to compute averages\n");
        return EXIT_FAILURE;
    }

    printf("Averages: ");
    for (j = 0; j < COLS; j++) {
        printf("%.2f", averages[j]);
        if (j < COLS - 1) {
            printf(", ");
        }
    }
    printf("\n");

    return EXIT_SUCCESS;
}