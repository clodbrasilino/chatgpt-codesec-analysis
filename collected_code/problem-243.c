#include<stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int countOccurrences(int arr[], int n, int target) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            count++;
        }
    }
    return count;
}

void sortByFirstOccurrence(int arr[], int n) {
    int firstElement = arr[0];
    int numOccurrences = countOccurrences(arr, n, firstElement);
    bubbleSort(arr, n);
    while (numOccurrences > 0) {
        int i = 0;
        while (arr[i] != firstElement) {
            i++;
        }
        int j = i;
        while (arr[j] == firstElement) {
            j++;
        }
        bubbleSort(arr+i, j-i);
        numOccurrences--;
    }
}

int main() {
    int arr[] = {4, 2, 1, 4, 3, 4, 2, 1, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    sortByFirstOccurrence(arr, n);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    
    return 0;
}