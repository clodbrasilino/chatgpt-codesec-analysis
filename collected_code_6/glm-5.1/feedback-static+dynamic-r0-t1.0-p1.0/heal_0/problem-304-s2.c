#include <stdio.h>
#include <stdlib.h>

int find_element(int *arr, int n, int rotations, int index) {
    if (arr == NULL || n <= 0 || index < 0 || index >= n) {
        return -1;
    }
    int effective_rotations = rotations % n;
    int new_index = (index - effective_rotations + n) % n;
    return arr[new_index];
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int rotations = 2;
    int index = 3;
    int result = find_element(arr, n, rotations, index);
    printf("%d\n", result);
    return 0;
}