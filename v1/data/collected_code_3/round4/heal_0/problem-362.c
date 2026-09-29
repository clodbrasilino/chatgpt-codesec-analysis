#include <stdio.h>
#include <stdlib.h>

int findMaxOccurrence(int* arr, int n) {
    int maxCount = 0;
    int maxItem = -1;
    for(int i = 0; i < n; i++) {
        int count = 0;
        for(int j = 0; j < n; j++) {
            if(arr[j] == arr[i])
                count++;
        }
        if(count > maxCount) {
            maxCount = count;
            maxItem = arr[i];
        }
    }
    return maxItem;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    int maxOccurrenceItem = findMaxOccurrence(arr, n);
    printf("Item with maximum occurrences: %d\n", maxOccurrenceItem);
    free(arr);
    return 0;
}