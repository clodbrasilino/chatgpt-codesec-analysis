#include <stdio.h>

int findFirstOdd(int* arr, int size) {
    for(int i = 0; i < size; i++) {
        if(arr[i] % 2 != 0) {
            return arr[i];
        }
    }
    return -1;
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 11, 12, 14};
    int size = sizeof(arr) / sizeof(arr[0]);
    int firstOdd = findFirstOdd(arr, size);
    if(firstOdd != -1) {
        printf("First odd number is %d\n", firstOdd);
    } else {
        printf("No odd number found\n");
    }
    return 0;
}