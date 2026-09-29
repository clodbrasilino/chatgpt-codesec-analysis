#include <stdio.h>

int findOddOccurrence(int arr[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result = result ^ arr[i];
    }
    return result;
}

int main() {
    int arr[] = {1, 2, 3, 2, 3, 1, 3};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf ("Element occurring odd number of times is %d \n", findOddOccurrence(arr, size));
    return 0;
}