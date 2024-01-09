#include <stdio.h>

int countSublists(int element, int arr[], int size) {
    int count = 0;
    
    for (int i = 0; i < size; i++) {
        int j = i;
        
        while (arr[j] == element && j < size) {
            j++;
        }
        
        if (j > i) {
            count++;
        }
        
        i = j;
    }
    
    return count;
}

int main() {
    int arr[] = {1, 2, 3, 1, 4, 1, 5, 6, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    int element = 1;
    int sublistCount = countSublists(element, arr, size);
    
    printf("Number of sublists containing %d: %d\n", element, sublistCount);
    
    return 0;
}