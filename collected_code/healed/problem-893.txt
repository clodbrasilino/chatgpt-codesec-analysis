#include <stdio.h>

void getLastElement(int arr[][3], int rows) {
    for (int i = 0; i < rows; i++) {
        int lastElement = arr[i][2];
        printf("Last element of sublist %d: %d\n", i + 1, lastElement);
    }
}

int main() {
    int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = sizeof(arr) / sizeof(arr[0]);
    
    getLastElement(arr, rows);
    
    return 0;
}