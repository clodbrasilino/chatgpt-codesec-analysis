#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 5

bool isEqual(int* array1, int* array2, int size) {
    for(int i = 0; i < size; i++){
        if(array1[i] != array2[i]){
            return false;
        }
    }
    return true;
}

int countUnique(int arrList[SIZE][SIZE], int listSize, int arrSize) {
    int count = listSize;

    for(int i = 0; i < listSize; i++) {
        for(int j = i + 1; j < listSize; j++) {
            if(isEqual(arrList[i], arrList[j], arrSize)) {
                count--;
                break;
            }
        }
    }

    return count;
}

int main() {
    int list[SIZE][SIZE] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {1, 2, 3, 4, 5},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };

    int uniqueCount = countUnique(list, SIZE, SIZE);

    printf("Number of unique arrays: %d\n", uniqueCount);

    return 0;
}