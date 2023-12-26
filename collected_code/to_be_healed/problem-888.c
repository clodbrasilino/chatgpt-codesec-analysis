#include<stdio.h>

void subtractNestedTuples(int tuple1[10][10], int tuple2[10][10], int rows, int columns) {
    int result[10][10];
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tuple1[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'tuple2[i][j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            result[i][j] = tuple1[i][j] - tuple2[i][j];
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tuple1[10][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int tuple2[10][10] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int rows = 3;
    int columns = 3;
    
    subtractNestedTuples(tuple1, tuple2, rows, columns);
    return 0;
}