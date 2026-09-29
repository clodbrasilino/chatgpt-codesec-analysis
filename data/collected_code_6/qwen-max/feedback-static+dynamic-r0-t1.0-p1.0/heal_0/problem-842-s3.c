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
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = findOddOccurrence(arr, n);
    if (result != -1) {
        printf("The number occurring odd number of times is: %d\n", result);
    } else {
        printf("No number occurs an odd number of times.\n");
    }
    return 0;
}