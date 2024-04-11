#include <stdio.h>

double findAverage(int arr[][3], int m, int n) {
    int sum = 0;
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            sum += arr[i][j];
            count++;
        }
    }
    return (double)sum / count;
}

int main() {
    int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
    double avg = findAverage(arr, 2, 3);
    printf("Average value = %.2f", avg);
    return 0;
}