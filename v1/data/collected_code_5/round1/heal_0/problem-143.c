#include<stdio.h>

#define MAX_SIZE 1000

int count_arrays(int arr[][MAX_SIZE], int size) {
    int count = 0;
    for(int i=0; i<size; i++) {
        if(arr[i][0] != '\0') 
            count++;
    }
    return count;
}

int main() {
    // define and populate the arrays
    int arr[][MAX_SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
    };
    int size = sizeof(arr) / sizeof(arr[0]);
    int total_arrays = count_arrays(arr, size);
    printf("Number of arrays: %d\n", total_arrays);
    return 0;
}