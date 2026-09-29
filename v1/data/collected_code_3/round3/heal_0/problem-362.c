#include <stdio.h>
#include <stdlib.h>

int maxOccurrence(int* arr, int size) {
    int max = 0, maxCount = 0, i, j;

    for (i = 0; i < size; i++) {
        int count = 1;
        for (j = i + 1; j < size; j++) {
            if (arr[j] == arr[i])
                count++;
            if (count > maxCount) {
                maxCount = count;
                max = arr[i];
            }
        }
    }
    return max;
}

int main() {
    int arr[] = {1, 3, 2, 1, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("%d", maxOccurrence(arr, n));
    return 0;
}