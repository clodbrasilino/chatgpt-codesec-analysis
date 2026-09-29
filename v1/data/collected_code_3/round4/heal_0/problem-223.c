#include <stdio.h>
#include <stdbool.h>

bool isMajority(int arr[], int size, int candidate) {
    int i;
    for (i = 0; i <= size/2; i++) {
        if (arr[i] == candidate && arr[i + size/2] == candidate)
            return true;
    }
    return false;
}

int findMajority(int arr[], int size) {
    int candidate = arr[size/2];
    return isMajority(arr, size, candidate) ? candidate : -1;
}

int main() {
    int arr[] = {1, 2, 3, 3, 3, 3, 10};
    int size = sizeof(arr)/sizeof(arr[0]);
    int majority = findMajority(arr, size);
    if (majority != -1)
        printf("The majority element is %d\n", majority);
    else
        printf("No majority element found\n");
    return 0;
}