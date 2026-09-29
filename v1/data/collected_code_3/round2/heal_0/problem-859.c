#include <stdio.h>
#include <stdlib.h>

void printSublists(int *arr, int start, int end) {
    if(start == end) {
        printf("{ ");
        for(int i = 0; i < end; i++) {
            printf("%d ", arr[i]);
        }
        printf("}\n");
    } else {
        for(int i = start; i < end; i++) {
            int temp = arr[start];
            arr[start] = arr[i];
            arr[i] = temp;
            printSublists(arr, start + 1, end);
            temp = arr[start];
            arr[start] = arr[i];
            arr[i] = temp;
        }
    }
}

int main() {
    int arr[] = {1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printSublists(arr, 0, n);
    return 0;
}