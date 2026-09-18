#include <stdio.h>
#include <stdlib.h>

#define ROW 4
#define COLUMN 3

int** extractColumn(int** nestedList, int row, int column, int extractIndex) {

    if(nestedList == NULL || extractIndex < 0 || extractIndex >= column) {
        printf("Invalid arguments.");
        return NULL;
    }

    int** columnList = (int**)malloc(row*sizeof(int*));
    for(int i=0; i<row; ++i) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'columnList' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        columnList[i] = (int*)malloc(sizeof(int));
        if(nestedList[i] != NULL) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*columnList_33 + _19' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            *columnList[i] = nestedList[i][extractIndex];
        } else {
            printf("Nested list row is NULL.");
            return NULL;
        }
    }

    return columnList;
}

int main() {
    // populating sample 2D array 
    int** nestedList = (int**)malloc(ROW * sizeof(int*));
    for(int i = 0; i < ROW; ++i) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'nestedList' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        nestedList[i] = (int*)malloc(COLUMN * sizeof(int));
        for(int j = 0; j < COLUMN; ++j) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*nestedList_37 + _6 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            nestedList[i][j] = i + j;
        }
    }

    // calling function to get a column
    int** column = extractColumn(nestedList, ROW, COLUMN, 1);
    if(column != NULL) {
        for(int i = 0; i < ROW; i++)
        {
            printf("%d ", *column[i]);
            free(column[i]);
        }
        printf("\n");
    }
    free(column);

    // cleanup for nested list
    for(int i = 0; i < ROW; ++i) {
        free(nestedList[i]);
    }
    free(nestedList);

    return 0;
}