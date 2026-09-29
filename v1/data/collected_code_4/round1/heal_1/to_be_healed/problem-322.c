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

    *positions = (int *)malloc(sizeof(int) * (*posLen));
    int posIndex = 0;

    for(i = 0; i < len; i++){
        if(list[i] == minValue){
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'positions' [CWE-690] [-Wanalyzer-possible-null-dereference]
             *  dereference of possibly-NULL '*positions' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            (*positions)[posIndex++] = i;
        }
    }
}

int main() {
    int list[] = {1, 2, 3, 2, 1, 0, 1, 2, 3, 0};
    int len = sizeof(list)/sizeof(list[0]);

    int *positions = NULL;
    int posLen;

    findMinPositions(list, len, &positions, &posLen);

    int i;
    for(i = 0; i < posLen; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'positions' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  use of uninitialized value '*positions.1_1 + _3' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        printf("%d ", positions[i]);
    }

    free(positions);
    
    return 0;
}
