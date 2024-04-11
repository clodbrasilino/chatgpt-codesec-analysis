#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    int rows;
    int cols;
} NestedList;

NestedList* createNestedList(int rows, int cols) {
    NestedList* list = malloc(sizeof(NestedList));
    list->rows = rows;
    list->cols = cols;
    list->data = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
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