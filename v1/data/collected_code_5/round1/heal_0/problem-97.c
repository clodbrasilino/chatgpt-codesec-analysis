#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 4

void countFrequency(int arr[ROWS][COLS]) {
    int count[10] = {0};

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (arr[i][j] >= 0 && arr[i][j] < 10) {
                count[arr[i][j]]++;
            } else {
                printf("Invalid number: %d", arr[i][j]);
                exit(1);
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (count[i] != 0) {
            printf("%d appears %d times\n", i, count[i]);
        }
    }
}

int main() {
    int arr[ROWS][COLS] = {
        {1, 2, 3, 4},
        {2, 3, 4, 1},
        {3, 1, 2, 1}
    };

    countFrequency(arr);

    return 0;
}