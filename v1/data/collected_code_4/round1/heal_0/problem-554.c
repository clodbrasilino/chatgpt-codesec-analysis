#include <stdio.h>

void findOdd(int arr[], int n){
    for(int i=0; i<n; i++)
    {
        if(arr[i]%2 != 0)
        {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main(){
    int arr[] = {12, 34, 7, 8, 9, 45, 68, 79, 20, 33};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf( "Odd numbers in the given array are :\n");
    findOdd(arr, n);
    
    return 0;
}