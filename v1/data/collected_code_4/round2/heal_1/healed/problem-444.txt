#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple{
    int *data;
    int size;
} Tuple;

void printTuple(Tuple *tuple) {
    for(int i=0; i < tuple->size; i++) {
        printf("%d ", tuple->data[i]);
    }
    printf("\n");
}

Tuple* trimByK(Tuple *inputTuple, int k) {
    if(inputTuple == NULL || k < 0 || k >= inputTuple->size){
        return NULL;
    }

    Tuple *trimmedTuple = (Tuple*)malloc(sizeof(Tuple));
    if(trimmedTuple == NULL) {
        return NULL;
    }
    
    trimmedTuple->size = inputTuple->size-k;
    trimmedTuple->data = malloc(trimmedTuple->size * sizeof(int));

    if(trimmedTuple->data == NULL) {
        free(trimmedTuple);
        return NULL;
    }

    for(int i = 0; i < trimmedTuple->size; i++) {
        trimmedTuple->data[i] = inputTuple->data[i];
    }
    return trimmedTuple;
}

int main() {
    Tuple tuple = {
        .data = (int []){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        .size = 10
    };
    
    int k = 3;
    
    Tuple *trimmedTuple = trimByK(&tuple, k);
    
    if(trimmedTuple != NULL) {
        printTuple(trimmedTuple);
        free(trimmedTuple->data);
        free(trimmedTuple);
    } else {
        printf("Invalid K or Tuple\n");
    }

    return 0;
}