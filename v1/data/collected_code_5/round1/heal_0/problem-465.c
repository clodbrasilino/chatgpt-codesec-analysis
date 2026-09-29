#include<stdio.h>

void dropEmptyItems(int arr[], int n) {
    // Pointer to iterate the array
    int *temp = arr;

    // Traversing the array
    for (int i = 0; i < n; i++) {
        // If element != 0, put the element at next position from beginning
        if (arr[i] != 0)
            *(temp++) = arr[i];
    }

    // Fill rest of the array as 0
    while (temp < (arr + n))
        *(temp++) = 0;
}
	
int main() {
    // initialize array
    int arr[] = { 0, 1, 2, 0, 3, 0, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    dropEmptyItems(arr, n);

    //Print modified array
    printf("Modified array is: ");
    for (int i=0; i<n; i++)
        printf("%d ", arr[i]);

    return 0;
}