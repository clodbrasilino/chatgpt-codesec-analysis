#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int frequency[MAX][MAX];

void findFrequency(int arr[][MAX], int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            frequency[arr[i][j]][0]++;
        }
    }
}

int main() {
    int arr[][MAX] = {{1, 2, 3, 2, 1},
                      {4, 5, 6, 5, 4},
                      {7, 8, 9, 8, 7}};
    int rows = sizeof(arr) / sizeof(arr[0]);
    int cols = sizeof(arr[0]) / sizeof(arr[0][0]);

    findFrequency(arr, rows, cols);

    for(int i = 0; i < MAX; i++) {
        if(frequency[i][0] > 0) {
            printf("Frequency of %d = %d\n", i, frequency[i][0]);
        }
    }

    return 0;
}