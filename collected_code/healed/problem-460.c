#include<stdio.h>

void printFirstElement(const int arr[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        printf("First element of sublist %d: %d\n", i + 1, arr[i][0]);
    }
}

int main() {
    const int myList[][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = sizeof(myList) / sizeof(myList[0]);
    int cols = sizeof(myList[0]) / sizeof(myList[0][0]);
  
    printFirstElement(myList, rows, cols);
  
    return 0;
}