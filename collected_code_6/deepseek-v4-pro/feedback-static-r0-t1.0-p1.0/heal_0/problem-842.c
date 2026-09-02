#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(const int *array, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= array[i];
    }
    return result;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 3, 1, 3};
    int size = (int)(sizeof(arr) / sizeof(arr[0]));
    int odd_number = find_odd_occurrence(arr, size);
    printf("%d\n", odd_number);
    return 0;
}