#include <stdio.h>

void repeatElements(int arr[], int size){
    for(int i = 0; i < size; i++){
        if(arr[i] <= 0){
            printf("Error! Encountered a non positive integer: %d\n", arr[i]);
            return;
        }
        for(int j = 0; j < arr[i]; j++){
            printf("%d ", arr[i]);
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    repeatElements(arr, size);

    return 0;
}