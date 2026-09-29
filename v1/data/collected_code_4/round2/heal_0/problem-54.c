#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

void countingSort(int arr[], int n) {
    int i, j, k, temp;
    int count[MAX] = {0};
    int output_array[n]; 

    for(i = 0; i < n; ++i) {
        ++count[arr[i]];
        if(arr[i] > MAX){
            printf("Error: Element larger than range.\n");
            return;
        }
    }
    
    k = 0;

    for(i = 0; i < MAX; ++i) {
        temp = count[i];
        for(j = 0; j < temp; ++j) {
            output_array[k] = i;
            ++k;
        }
    }
    
    for(i = 0; i < n; ++i)
        arr[i] = output_array[i];
}

int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    int i;

    countingSort(arr, n);

    printf("Sorted array is: \n");
    for(i = 0; i < n; ++i)
        printf("%d ", arr[i]);

    return 0;
}