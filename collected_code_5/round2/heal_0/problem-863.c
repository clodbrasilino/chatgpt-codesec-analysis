#include <stdio.h>

int longestConsecutiveSubsequence(int arr[], int size) {
    int number, sequence;
    int i, j;
    number = 1;
    sequence = 1;

    for(i = 0; i < size - 1; i++) {
        if (arr[i+1] == arr[i] + 1) {
        number++;
        if (number > sequence) sequence = number;
        } else {
        number = 1;
        }
    }
    return sequence;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(arr) / sizeof(int);

    int result = longestConsecutiveSubsequence(arr, size);
    printf("%d\n", result);

    return 0;
}