#include <stdio.h>
#include <stdlib.h>

int countOddElements(int *list, int length) {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (list[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = sizeof(arr) / sizeof(arr[0]);
    int oddCount = countOddElements(arr, length);
    printf("Number of odd elements: %d\n", oddCount);
    return 0;
}