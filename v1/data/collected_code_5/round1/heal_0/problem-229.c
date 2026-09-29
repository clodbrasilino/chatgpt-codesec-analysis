#include <stdio.h>

void rearrange(int arr[], int size){
    int temp;
    int i = 0;
    int j = size - 1;
    while(i < j){
        while(arr[i] < 0 && i < j)
            i++;
        while(arr[j] >= 0 && i < j)
            j--;
        if(i < j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

void printArray(int arr[], int size){
    for(int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(){
    int arr[] = {-12, 11, -13, -5, 6, -7, 5, -3, -6};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array is: \n");
    printArray(arr, size);

    rearrange(arr, size);

    printf("Re-arranged array is: \n");
    printArray(arr, size);

    return 0;
}