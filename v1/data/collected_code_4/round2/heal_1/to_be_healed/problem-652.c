#include<stdio.h>
#include<stdlib.h>

#define ROW 3
#define COL 4

typedef struct tuple {
    int x, y, val;
} tuple;

tuple* createTuple(int x, int y, int val) {
    tuple *new_tuple = (tuple*) malloc(sizeof(tuple));
    if(new_tuple == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_tuple->x = x;
    new_tuple->y = y;
    new_tuple->val = val;
    return new_tuple;
}

tuple** flattenMatrix(int matrix[ROW][COL]) {
    tuple **flattened = (tuple**) malloc(COL * sizeof(tuple*));
    if(flattened == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i < COL; i++) {
        for(int j = 0; j < ROW; j++) {
            /* Possible weaknesses found:
             *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            flattened[i] = createTuple(i, j, matrix[j][i]);
        }
    }
    return flattened;
}

void printTuples(tuple **tuples, int size) {
    for(int i = 0; i < size; i++) {
        printf("(%d, %d): %d\n", tuples[i]->x, tuples[i]->y, tuples[i]->val);
    }
}

void freeTuples(tuple **tuples, int size) {
    for(int i = 0; i < size; i++) {
        free(tuples[i]);
    }
    free(tuples);
}

int main(void) {
    int matrix[ROW][COL] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12}};
    tuple **flattened = flattenMatrix(matrix);
    printTuples(flattened, COL);
    freeTuples(flattened, COL);
    return 0;
}