#include <stdio.h>

int findMinimum(const int arr[], int low, int high)
{
    if (high < low) {
        return -1;
    }
    
    if (low == high) {       
        return arr[low];
    }
    
    int mid = low + (high - low) / 2;
        
    if (mid < high && arr[mid + 1] < arr[mid]) {
        return arr[mid + 1];
    }
    
    if (mid > low && arr[mid] < arr[mid - 1]) {
        return arr[mid];
    }
    
    if (arr[high] > arr[low]) {
        return findMinimum(arr, low, mid - 1);
    }
    
    return findMinimum(arr, mid + 1, high);
}

int main()
{
    int arr[] = {4, 5, 6, 7, 8, 9, 1, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
        
    int min = findMinimum(arr, 0, n - 1);
    
    if(min != -1){
        printf("The minimum element in the array is: %d\n", min);
    } 
    else {
        printf("Array is empty or not rotated\n");
    }
    
    return 0;
}