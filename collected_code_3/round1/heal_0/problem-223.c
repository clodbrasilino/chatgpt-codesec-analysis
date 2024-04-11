#include <stdio.h>
#include <stdbool.h>

bool isMajority(int arr[], int size, int candidate) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == candidate) {
            count++;
        }
    }
    return count > size / 2;
}

int findMajority(int arr[], int size) {
    int majorityIndex = size / 2;
    if (isMajority(arr, size, arr[majorityIndex])) {
        return arr[majorityIndex];
    }
    return -1;
}

int main() {
    int arr[] = {1, 2, 3, 3, 3, 3, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    int majority = findMajority(arr, size);
    if (majority != -1) {
        printf("Majority element is %d\n", majority);
    } else {
        printf("No majority element found\n");
    }
    return 0;
}