#include <stdio.h>
#include <stdlib.h>

double find_average(int **data, int n, int m) {
    double sum = 0.0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sum += data[i][j];
            count++;
        }
    }
    return (count > 0) ? sum / count : 0.0;
}

int main() {
    int n = 3;
    int m = 2;
    int data[][2] = {{1, 2}, {3, 4}, {5, 6}};

    int *data_ptr[n];
    for (int i = 0; i < n; i++) {
        data_ptr[i] = data[i];
    }

    double average = find_average(data_ptr, n, m);
    printf("Average: %.2f\n", average);

    return 0;
}