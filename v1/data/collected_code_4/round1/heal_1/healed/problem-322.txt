#include <stdio.h>
#include <stdlib.h>

void findMinPositions(int* list, int len, int** positions, int* posLen) {
    int i;
    int minValue = list[0];

    for(i = 1; i < len; i++){
        if(list[i] < minValue){
            minValue = list[i];
        }
    }

    *posLen = 0;
    for(i = 0; i < len; i++){
        if(list[i] == minValue){
            (*posLen)++;
        }
    }

    if(*posLen > 0) {
        *positions = (int *)malloc(sizeof(int) * (*posLen));

        if(*positions) {
            int posIndex = 0;
            for(i = 0; i < len; i++){
                if(list[i] == minValue){
                    (*positions)[posIndex++] = i;
                }
            } 
        }
        else {
            *posLen = 0;
        }
    }
}

int main() {
    int list[] = {1, 2, 3, 2, 1, 0, 1, 2, 3, 0};
    int len = sizeof(list)/sizeof(list[0]);

    int *positions = NULL;
    int posLen;

    findMinPositions(list, len, &positions, &posLen);

    if(positions) {
        int i;
        for(i = 0; i < posLen; i++) {
            printf("%d ", positions[i]);
        }
        free(positions);
    }

    return 0;
}