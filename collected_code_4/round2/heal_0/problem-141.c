#include <stdio.h> 

void flip(int array[], int i) {
    int temp, start = 0;
    while (start < i) 
    {
        temp = array[start];
        array[start] = array[i];
        array[i] = temp;
        start++;
        i--;
    } 
}

int findMaxIndex(int array[], int n) {
    int max_idx, i;
    for(max_idx = 0, i = 0; i < n; i++) 
        if(array[i] > array[max_idx])
            max_idx = i;
    return max_idx;
}

void pancakeSort(int array[], int n) {
    int mi, i;
    for(i = n; i > 1; i--) {
        mi = findMaxIndex(array, i);
        if(mi != i-1) {
            flip(array, mi);
            flip(array, i-1);
        }
    }
}

void printArray(int array[], int size) {
    int i;
    for(i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main() {
    int array[] = {23, 10, 20, 11, 12, 6, 7};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Unsorted array: \n");
    printArray(array, n);

    pancakeSort(array, n);

    printf("Sorted array: \n");
    printArray(array, n);
    return 0;
}