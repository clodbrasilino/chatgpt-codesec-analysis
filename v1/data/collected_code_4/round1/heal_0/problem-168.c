#include <stdio.h>

int find_frequency(int n, int* arr, int arr_size) {
    int count = 0;
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] == n) {
            count++;
        }
    }
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 4, 2, 3, 2, 1};
    int number = 2;
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int frequency = find_frequency(number, arr, arr_size);
    printf("The frequency of %d in the array is: %d\n", number, frequency);
    return 0;
}