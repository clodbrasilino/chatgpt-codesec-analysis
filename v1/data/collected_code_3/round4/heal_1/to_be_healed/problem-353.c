#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    int rows;
    int cols;
} NestedList;

NestedList* createNestedList(int rows, int cols) {
    NestedList* list = malloc(sizeof(NestedList));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list->rows = rows;
    list->cols = cols;
    list->data = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*list.data + (long unsigned int)i * 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list->data[i] = malloc(cols * sizeof(int));
    }
    return list;
}

void deleteNestedList(NestedList* list) {
    for (int i = 0; i < list->rows; i++) {
        free(list->data[i]);
    }
    free(list->data);
    free(list);
}

void removeColumn(NestedList* list, int col) {
    for (int i = 0; i < list->rows; i++) {
        for (int j = col; j < list->cols - 1; j++) {
            list->data[i][j] = list->data[i][j + 1];
        }
        list->data[i] = realloc(list->data[i], (list->cols - 1) * sizeof(int));
    }
    list->cols--;
}

int main() {
    NestedList* list = createNestedList(3, 3);
    for (int i = 0; i < list->rows; i++) {
        for (int j = 0; j < list->cols; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*_3 + _5 + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
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