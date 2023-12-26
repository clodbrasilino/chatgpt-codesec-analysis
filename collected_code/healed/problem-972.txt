#include <stdio.h>
#include <stdlib.h>

int** concatenateTuples(const int* tuple1, const int* tuple2, int size1, int size2) {
    int** nestedTuple = (int**) malloc((size1 + size2) * sizeof(int*));
    
    if(nestedTuple == NULL) {
        return NULL;
    }

    for (int i = 0; i < size1; i++) {
        nestedTuple[i] = (int*) malloc(sizeof(int));
        if(nestedTuple[i] == NULL) {
            for(int j = 0; j < i; j++) {
                free(nestedTuple[j]);
            }
            free(nestedTuple);
            return NULL;
        }
        nestedTuple[i][0] = tuple1[i];
    }
    
    for (int i = 0; i < size2; i++) {
        nestedTuple[size1 + i] = (int*) malloc(sizeof(int));
        if(nestedTuple[size1 + i] == NULL) {
            for(int j = 0; j < size1 + i; j++) {
                free(nestedTuple[j]);
            }
            free(nestedTuple);
            return NULL;
        }
        nestedTuple[size1 + i][0] = tuple2[i];
    }
    
    return nestedTuple;
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int** nestedTuple = concatenateTuples(tuple1, tuple2, 3, 3);

    if(nestedTuple == NULL) {
        printf("Error: could not allocate memory for nestedTuple.");
        return 1;
    }
    
    for (int i = 0; i < 6; i++) {
        printf("%d\n", nestedTuple[i][0]);
    }

    for (int i = 0; i < 6; i++) {
        free(nestedTuple[i]);
    }
    free(nestedTuple);
    
    return 0;
}