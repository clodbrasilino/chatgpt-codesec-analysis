#include <stdio.h>

int findOddOccurrence(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        int count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count % 2 != 0) {
            return arr[i];
        }
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 2, 3, 1, 3};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findOddOccurrence(arr, size);
    if (result != -1) {
        printf("The number with odd occurrences is: %d\n", result);
    } else {
        printf("No number with odd occurrences found.\n");
    }
    return 0;
}