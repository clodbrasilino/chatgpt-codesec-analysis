#include<stdio.h>

void printFirstElement(int arr[][10], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'arr[i][0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("First element of sublist %d: %d\n", i + 1, arr[i][0]);
    }
}

int main() {
    int myList[][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int rows = sizeof(myList) / sizeof(myList[0]);
    int cols = sizeof(myList[0]) / sizeof(myList[0][0]);
  
    printFirstElement(myList, rows, cols);
  
    return 0;
}