#include <stdio.h>
#include <stdlib.h>

void extractColumn(int* list, int numRows, int column, int numColumns) {
    for (int i = 0; i < numRows; i++) {
        printf("%d ", *(list + i*numColumns + column));
    }
}

int main() {
    int nestedList[5][3] = {{1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9},
                            {10, 11, 12},
                            {13, 14, 15}};
    int columnToExtract = 1;
    
    extractColumn((int *)nestedList, 5, columnToExtract, 3);
    
    return 0;
}