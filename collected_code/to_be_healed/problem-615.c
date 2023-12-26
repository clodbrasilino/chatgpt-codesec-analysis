#include <stdio.h>

double findAverage(int** tuples, int rows, int columns) {
    int sum = 0;
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuples[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
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

    double average = findAverage((int**)tuples, 3, 4);
    printf("Average: %.2lf\n", average);

    return 0;
}