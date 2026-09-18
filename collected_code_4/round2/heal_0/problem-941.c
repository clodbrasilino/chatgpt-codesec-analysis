#include <stdio.h>

int countElements(int *array, int sentinel, int size){
    int count = 0;
    for(int i = 0; i < size; i++){
        if(array[i] == sentinel){
            return count;
        }
        count++;
    }
    return count;
}

int main(){
    int data[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(data) / sizeof(data[0]);
    int sentinel = 3; // Equivalent to 'tuple' in this case
    printf("Elements before sentinel: %d\n", countElements(data, sentinel, size));
    return 0;
}