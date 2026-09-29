#include<stdlib.h>
#include<stdio.h>

void printDuplicates(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        if(a[abs(a[i])] >= 0)
          a[abs(a[i])] = -a[abs(a[i])];
        else
          printf("%d ", abs(a[i]));
    }      
}

int main()
{
    int arr[] = {1, 2, 3, 1, 3, 6, 6};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    printDuplicates(arr, arr_size);
    return 0;
}