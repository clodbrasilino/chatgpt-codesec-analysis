#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int areElementsUnique(int arr[], int size){
    for(int i = 0; i < size; i++){
        for(int j = i + 1; j < size; j++){
            if(arr[i] == arr[j]){
                return 0;
            }
        }
    }
    return 1;
}

int main(){
    int arr[SIZE];
    for(int i = 0; i < SIZE; i++){
        printf("Enter element number %d: ", i+1);
        scanf("%d", &arr[i]);
    }
	
    if(areElementsUnique(arr, SIZE)){
        printf("Elements are unique.\n");
    }else{
        printf("Elements are not unique.\n");
    }
	
    return 0;
}