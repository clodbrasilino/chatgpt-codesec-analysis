#include <stdio.h>
#include <stdlib.h>

int findSmallestMissingNumber(int array[], int n) {
    int i, j;
    int smallest = 1;

    for (i = 0; i < n; i++) {
        if (array[i] == smallest) {
            smallest++;
            i = -1;
        }
    }
    return smallest;
}

int main() {
    int array[] = {1, 2, 3, 5, 6, 7, 9};
    int n = sizeof(array) / sizeof(array[0]);
    int missingNumber = findSmallestMissingNumber(array, n);
    printf("The smallest missing number is %d\n", missingNumber);
    return 0;
}