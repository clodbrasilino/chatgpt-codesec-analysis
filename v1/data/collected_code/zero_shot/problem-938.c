#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void threeClosestElements(int arr1[], int arr2[], int arr3[], int n1, int n2, int n3) {
    int i = 0, j = 0, k = 0;
    int diff = INT_MAX;
    int res1, res2, res3;
  
    while (i < n1 && j < n2 && k < n3) {
        int minimum = min(arr1[i], min(arr2[j], arr3[k]));
        int maximum = max(arr1[i], max(arr2[j], arr3[k]));
        
        if (maximum - minimum < diff) {
            diff = maximum - minimum;
            res1 = arr1[i];
            res2 = arr2[j];
            res3 = arr3[k];
        }
        
        if (minimum == arr1[i]) {
            i++;
        } else if (minimum == arr2[j]) {
            j++;
        } else {
            k++;
        }
    }
    
    printf("Closest elements: %d %d %d\n", res1, res2, res3);
}

int main() {
    int arr1[] = {1, 4, 10};
    int arr2[] = {2, 15, 20};
    int arr3[] = {10, 12};
  
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
  
    threeClosestElements(arr1, arr2, arr3, n1, n2, n3);
  
    return 0;
}
