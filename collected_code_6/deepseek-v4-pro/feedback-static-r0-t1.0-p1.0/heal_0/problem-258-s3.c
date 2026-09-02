#include <stdio.h>

int count_odd_elements(int arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = count_odd_elements(arr, size);
    printf("Number of odd elements: %d\n", result);
    return 0;
}