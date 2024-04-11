#include <stdio.h>
#include <stdlib.h>

int findMaxOccurrence(int* arr, int n) {
    int maxCount = 0;
    int maxItem = arr[0];
    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            maxCount = count;
            maxItem = arr[i];
        }
    }
    return maxItem;
}

int main() {
    int arr[] = {1, 3, 2, 1, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxOccurrenceItem = findMaxOccurrence(arr, n);
    printf("Item with maximum occurrences: %d\n", maxOccurrenceItem);
    return 0;
}