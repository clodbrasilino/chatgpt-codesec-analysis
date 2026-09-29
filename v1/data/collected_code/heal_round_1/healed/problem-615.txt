#include <stdio.h>

double findAverage(int rows, int columns, int tuples[rows][columns]) {
    int sum = 0;
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            sum += tuples[i][j];
            count++;
        }
    }

    return (double)sum / count;
}

int main() {
    int tuples[3][4] = {{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12}};

    double average = findAverage(3, 4, tuples);
    printf("Average: %.2lf\n", average);

    return 0;
}