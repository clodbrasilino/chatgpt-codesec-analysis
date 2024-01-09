#include <stdio.h>
#include <stdlib.h>

// Function to concatenate two tuples into a nested tuple
int** concatenateTuples(int* tuple1, int* tuple2, int size1, int size2) {
    int** nestedTuple = (int**) malloc((size1 + size2) * sizeof(int*));
    
    // Copy elements from tuple1 to nestedTuple
    for (int i = 0; i < size1; i++) {
        nestedTuple[i] = (int*) malloc(sizeof(int));
        nestedTuple[i][0] = tuple1[i];
    }
    
    // Copy elements from tuple2 to nestedTuple
    for (int i = 0; i < size2; i++) {
        nestedTuple[size1 + i] = (int*) malloc(sizeof(int));
        nestedTuple[size1 + i][0] = tuple2[i];
    }
    
    return nestedTuple;
}

int main() {
    int tuple1[] = {1, 2, 3};
    int tuple2[] = {4, 5, 6};
    int** nestedTuple = concatenateTuples(tuple1, tuple2, 3, 3);
    
    // Print the nestedTuple
    for (int i = 0; i < 6; i++) {
        printf("%d\n", nestedTuple[i][0]);
    }
    
    // Free memory allocated for nestedTuple
    for (int i = 0; i < 6; i++) {
        free(nestedTuple[i]);
    }
    free(nestedTuple);
    
    return 0;
}