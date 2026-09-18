#include<stdio.h> 
#include<stdlib.h> 

int comparator(const void* p, const void* q) 
{ 
    return ( *(int*)p - *(int*)q ); 
} 

void print_max_min_elements(int arr[], int count, int k) 
{ 
    //Sorting the array.
    qsort((void*)arr, count, sizeof(arr[0]), comparator);

    //Printing the maximum and minimum k elements 
    printf("Minimum %d elements is: \n", k); 
    for (int i = 0; i<k ; i++)
        printf("%d ", arr[i]); 

    printf("\n\nMaximum %d elements is: \n", k); 
    for (int i = count-k; i<count ; i++)
        printf("%d ", arr[i]); 
} 

int main() 
{ 
    //Test the function
    int arr[] = {1, 23, 12, 9, 30, 2, 50}; 
    int count = sizeof(arr)/sizeof(arr[0]); 
    int k = 3; 

    print_max_min_elements(arr, count, k); 

    return 0; 
} 