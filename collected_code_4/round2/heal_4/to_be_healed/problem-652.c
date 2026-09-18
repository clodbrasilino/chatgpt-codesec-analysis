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
    tuple **flattened = (tuple**) malloc(COL * ROW * sizeof(tuple*));
    if(flattened == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int k = 0;
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            flattened[k] = createTuple(i, j, matrix[i][j]);
            k++;
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
        /* Possible weaknesses found:
         *  use of uninitialized value '*tuples_13(D) + _2' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        free(tuples[i]);
        tuples[i] = NULL;
    }
    free(tuples);
    tuples = NULL;
}

int main(void) {
    int matrix[ROW][COL] = {{1, 2, 3, 4},{5, 6, 7, 8},{9, 10, 11, 12}};
    tuple **flattened = flattenMatrix(matrix);
    printTuples(flattened, ROW*COL);
    freeTuples(flattened, ROW*COL);
    return 0;
}