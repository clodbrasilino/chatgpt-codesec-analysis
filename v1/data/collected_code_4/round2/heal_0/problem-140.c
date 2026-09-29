#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

void find_single_elements(int *arr, int n) {
    int frequency[SIZE] = {0};
    int i;

    for(i = 0; i < n; i++) {
        frequency[arr[i]]++;
    }

    printf("Single elements are: ");
    for(i = 0; i < SIZE; i++) {
        if(frequency[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int arr[] = {9, 7, 2, 5, 5, 2, 6, 7, 19, 30};
    int n = sizeof(arr) / sizeof(arr[0]);

    find_single_elements(arr, n);

    return 0;
}