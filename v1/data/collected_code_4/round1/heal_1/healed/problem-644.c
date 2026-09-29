#include <stdio.h>

void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    int temp;

    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main() {
    int array[] = { 1, 2, 3, 4, 5, 6 };
    int num_elements = sizeof(array) / sizeof(array[0]);

    reverseArray(array, num_elements);

    for(int i = 0; i < num_elements; i++) {
        printf("%d ", array[i]);
    }

    return 0;
}