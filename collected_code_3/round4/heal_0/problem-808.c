#include <stdio.h>
#include <stdbool.h>

#define SIZE 5

bool checkTuple(int arr[][2], int n, int k) {
    for(int i = 0; i < n; i++) {
        if(arr[i][0] == k || arr[i][1] == k) {
            return true;
        }
    }
    return false;
}

int main() {
    int arr[SIZE][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}, {9, 10}};
    int k = 7;

    if(checkTuple(arr, SIZE, k)) {
        printf("Tuple contains %d\n", k);
    } else {
        printf("Tuple does not contain %d\n", k);
    }

    return 0;
}