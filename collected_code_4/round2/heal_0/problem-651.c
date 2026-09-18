#include <stdio.h>
#include <stdbool.h>

bool is_tuple_subset(int* arr1, int m, int* arr2, int n) {
    if(m>n) 
        return false;
  
    int i = 0;
    int j = 0;

    while( i < m && j < n){
        if(arr1[i] < arr2[j])
            i++;
        else if(arr2[j] < arr1[i])
            return false;
        else { 
            i++; 
            j++; 
        }
    }
  
    return (i < m)? false : true; 
}

int main() {
    int arr1[] = {2, 3, 5};
    int arr2[] = {1, 2, 3, 4, 5};
  
    int m = sizeof(arr1) / sizeof(arr1[0]);
    int n = sizeof(arr2) / sizeof(arr2[0]);
  
    if(is_tuple_subset(arr1, m, arr2, n))
        printf("arr1[] is subset of arr2[] \n");
    else
        printf("arr1[] is not a subset of arr2[] \n");
  
    return 0;
}