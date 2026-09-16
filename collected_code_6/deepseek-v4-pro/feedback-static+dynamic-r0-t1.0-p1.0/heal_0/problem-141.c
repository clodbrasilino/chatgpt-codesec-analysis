#include <stdio.h>
#include <stdlib.h>

void flip(int arr[], int i) {
    int temp, start = 0;
    while (start < i) {
        temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

int findMax(int arr[], int n) {
    int mi = 0;
    for (int i = 0; i < n; ++i)
        if (arr[i] > arr[mi])
            mi = i;
    return mi;
}

void pancakeSort(int arr[], int n) {
    for (int curr_size = n; curr_size > 1; --curr_size) {
        int mi = findMax(arr, curr_size);
        if (mi != curr_size - 1) {
            if (mi != 0)
                flip(arr, mi);
            flip(arr, curr_size - 1);
        }
    }
}

int main() {
    int arr[] = {23, 10, 20, 11, 12, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    pancakeSort(arr, n);
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    return 0;
}