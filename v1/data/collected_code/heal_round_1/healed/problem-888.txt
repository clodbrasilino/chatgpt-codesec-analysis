#include<stdio.h>

void subtractNestedTuples(const int tuple1[10][10], const int tuple2[10][10], int rows, int columns) {
    int result[10][10];
    
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            result[i][j] = tuple1[i][j] - tuple2[i][j];
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

int main() {
    const int tuple1[10][10] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const int tuple2[10][10] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int rows = 3;
    int columns = 3;
    
    subtractNestedTuples(tuple1, tuple2, rows, columns);
    return 0;
}