#include <stdio.h>

typedef struct {
    int index;
    int value;
} Tuple;

int getMinIndex(Tuple arr[], int size){
    int min = arr[0].value;
    int minIndex = arr[0].index;
    
    for(int i=1; i<size; i++){
        if(arr[i].value < min){
            min = arr[i].value;
            minIndex = arr[i].index;
        }
    }

    return minIndex;
}

int main() {
    Tuple arr[] = {{0, 20}, {1, 15}, {2, 30}, {3, 5}, {4, 40}};
    int size = sizeof(arr)/sizeof(arr[0]);

    int minIndex = getMinIndex(arr, size);
    
    printf("The index with minimum value is: %d\n", minIndex);

    return 0;
}