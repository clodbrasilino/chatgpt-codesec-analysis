#include <stdio.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform a single comb sort pass
int getNextGap(int gap) {
    gap = (gap * 10) / 13;
    if (gap < 1) {
        return 1;
    }
    return gap;
}

// Function to sort a list of elements using comb sort
void combSort(int arr[], int n) {
    int gap = n;
    int swapped = 1;

    while (gap != 1 || swapped == 1) {
        gap = getNextGap(gap);
        swapped = 0;

        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(&arr[i], &arr[i + gap]);
                swapped = 1;
            }
        }
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Example usage
int main() {
    int arr[] = {5, 2, 8, 9, 1, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    combSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}