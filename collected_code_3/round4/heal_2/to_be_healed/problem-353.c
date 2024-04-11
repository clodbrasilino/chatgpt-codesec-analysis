#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    int rows;
    int cols;
} NestedList;

NestedList* createNestedList(int rows, int cols) {
    NestedList* list = malloc(sizeof(NestedList));
    if(list == NULL) return NULL;

    list->rows = rows;
    list->cols = cols;

    list->data = malloc(rows * sizeof(int*));
    if(list->data == NULL) {
        free(list);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        list->data[i] = malloc(cols * sizeof(int));
        if(list->data[i] == NULL) {
            for(int j = 0; j < i; j++) free(list->data[j]);
            free(list->data);
            free(list);
            return NULL;
        }
    }
    return list;
}

void deleteNestedList(NestedList* list) {
    if(list == NULL) return;
    
    for (int i = 0; i < list->rows; i++) {
        free(list->data[i]);
    }
    free(list->data);
    free(list);
}

void removeColumn(NestedList* list, int col) {
    int** tempData;
    
    for (int i = 0; i < list->rows; i++) {
        for (int j = col; j < list->cols - 1; j++) {
            list->data[i][j] = list->data[i][j + 1];
        }
        tempData = realloc(list->data[i], (list->cols - 1) * sizeof(int));
        if(tempData == NULL) return;
        /* Possible weaknesses found:
         *  assignment to 'int *' from incompatible pointer type 'int **' [-Wincompatible-pointer-types]
         */
        else list->data[i] = tempData;
    }
    list->cols--;
}

int main() {
    NestedList* list = createNestedList(3, 3);
    if(list == NULL) return 0;

    for (int i = 0; i < list->rows; i++) {
        for (int j = 0; j < list->cols; j++) {
            list->data[i][j] = i * list->cols + j;
        }
    }
    removeColumn(list, 1);
   
    for (int i = 0; i < list->rows; i++) {
        for (int j = 0; j < list->cols; j++) {
            printf("%d ", list->data[i][j]);
        }
        printf("\n");
    }
    deleteNestedList(list);
    return 0;
}