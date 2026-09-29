#include<stdio.h>

void rotateList(int* list, int length, int rotations){
    int temp;
    
    // Rotate the list by one item to the right 'rotations' number of times
    for(int i = 0; i < rotations; i++){
        temp = list[length-1];
        
        for(int j = length-1; j > 0; j--){
            list[j] = list[j-1];
        }
        
        list[0] = temp;
    }
}

int main(){
    int list[] = {1, 2, 3, 4, 5};
    int length = sizeof(list) / sizeof(list[0]);
    int rotations = 2;
    
    rotateList(list, length, rotations);
    
    for(int i = 0; i < length; i++){
        printf("%d ", list[i]);
    }
    
    return 0;
}