#include <stdio.h>

void extractColumn(int list[][3], int numRows, int column) {
    for (int i = 0; i < numRows; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i][column]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        printf("%d ", list[i][column]);
    }
}

int main() {
    int nestedList[5][3] = {{1, 2, 3},
                            {4, 5, 6},
                            {7, 8, 9},
                            {10, 11, 12},
                            {13, 14, 15}};
    int columnToExtract = 1;
    
    extractColumn(nestedList, 5, columnToExtract);
    
    return 0;
}