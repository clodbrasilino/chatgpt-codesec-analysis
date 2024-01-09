#include <stdio.h>

void getLastElement(int arr[][3], int rows) {
    for (int i = 0; i < rows; i++) {
        int lastElement = arr[i][2];
        printf("Last element of sublist %d: %d\n", i + 1, lastElement);
    }
}

int main() {
    int sublist1[] = {1, 2, 3};
    int sublist2[] = {4, 5, 6};
    int sublist3[] = {7, 8, 9};
    
    int arr[][3] = {sublist1, sublist2, sublist3};
    int rows = sizeof(arr) / sizeof(arr[0]);
    
    getLastElement(arr, rows);
    
    return 0;
}