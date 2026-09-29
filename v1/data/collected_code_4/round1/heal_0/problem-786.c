#include <stdio.h>

int findInsertPosition(int* array, int value, int low, int high){
    if(high <= low)
        return (value > array[low])?  (low + 1): low;
 
    int mid = (low + high)/2;
 
    if(value == array[mid])
        return mid+1;
 
    if(value > array[mid])
        return findInsertPosition(array, value, mid+1, high);
    return findInsertPosition(array, value, low, mid-1);
}
 
void insertSorted(int* array, int n, int value){
    int position = findInsertPosition(array, value, 0, n-1);
    int j;
 
    for(j=n-1; j>=position; j--)
        array[j+1] = array[j];
 
    array[position] = value;
}
 
int main(){
    int array[20] = {10, 20, 30, 40, 50};
    int n = 5;
    int value = 35;

    insertSorted(array, n, value);
    n = n+1;
 
    printf("\nAfter Insertion\n");
    for (int i=0; i<n; i++)
        printf("%d ", array[i]);

    return 0;
}