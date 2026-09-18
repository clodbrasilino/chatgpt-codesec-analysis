#include <stdio.h>
#include <stdlib.h>

#define MAX_LISTS 5
#define MAX_ELEMENTS 5

int **zip(int src1[][MAX_ELEMENTS], int src2[][MAX_ELEMENTS], int rows) {
    int **result = malloc(rows * 2 * sizeof(int *));
    if(result == NULL){
        return NULL;
    }
    for(int i=0; i<rows; i++){
        result[i*2] = malloc(MAX_ELEMENTS * sizeof(int));
        result[i*2 +1] = malloc(MAX_ELEMENTS * sizeof(int));
        if(result[i*2]==NULL || result[i*2+1]==NULL){
            for(int j=0;j<i;j++){
                free(result[j*2]);
                free(result[j*2+1]);
            }
            free(result);
            return NULL;
        }
        for(int j=0;j<MAX_ELEMENTS;j++){
            result[i*2][j] = src1[i][j];
            result[i*2+1][j] = src2[i][j];
        }
    }
    return result;
}

int main() {
    int lists1[MAX_LISTS][MAX_ELEMENTS] = {{1, 2, 3, 4, 5},{6, 7, 8, 9, 10},{11, 12, 13, 14, 15},{16, 17, 18, 19, 20},{21, 22, 23, 24, 25}};
    int lists2[MAX_LISTS][MAX_ELEMENTS] = {{26, 27, 28, 29, 30},{31, 32, 33, 34, 35},{36, 37, 38, 39, 40},{41, 42, 43, 44, 45},{46, 47, 48, 49, 50}};
    int **zipped = zip(lists1, lists2, MAX_LISTS);
    if(zipped==NULL){
        printf("Memory allocation error");
    }
    else{
        for(int i=0; i<2*MAX_LISTS; i++){
            for(int j=0; j<MAX_ELEMENTS; j++){
                printf("%d, ", zipped[i][j]);
            }
            printf("\n");
        }
        for(int i=0;i<2*MAX_LISTS;i++){
            free(zipped[i]);
        }
        free(zipped);
    }
    return 0;
}