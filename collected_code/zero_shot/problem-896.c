#include <stdio.h>

void sortList(int arr[][2], int n) {
    int i, j, temp;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j][1] > arr[j+1][1]) {
                temp = arr[j][1];
                arr[j][1] = arr[j+1][1];
                arr[j+1][1] = temp;
            }
        }
    }
}

int main() {
    int arr[][2] = {{2, 1}, {4, 3}, {6, 5}, {8, 7}};
    int n = sizeof(arr)/sizeof(arr[0]);

    sortList(arr, n);

    printf("Sorted List:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)\n", arr[i][0], arr[i][1]);
    }

    return 0;
}