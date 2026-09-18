#include <stdio.h>

int find_last_index(int arr[], int len, int num) {
    int index = -1;
    for (int i = 0; i < len; i++) {
        if (arr[i] == num) {
            index = i;
        }
    }
    return index;
}

int main() {
    int arr[] = {1, 2, 3, 3, 5, 6, 7};
    int num = 3;
    int len = sizeof(arr) / sizeof(arr[0]);
    int result = find_last_index(arr, len, num);
    if (result != -1)
        printf("Last occurrence of %d is at index %d\n", num, result);
    else
        printf("Element not found in array\n");
}