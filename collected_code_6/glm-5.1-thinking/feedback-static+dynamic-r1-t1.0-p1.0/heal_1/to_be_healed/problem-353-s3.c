#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **data;
    int rows;
    int cols;
} NestedList;

int remove_column(NestedList *list, int col) {
    /* Possible weaknesses found:
     *  Assuming that condition 'list->cols<=col' is not redundant
     */
    if (list == NULL || col < 0 || list->cols <= col || (list->rows > 0 && list->data == NULL)) {
        return -1;
    }
    /* Possible weaknesses found:
     *  Assignment 'new_cols=list->cols-1', assigned value is greater than 1
     */
    int new_cols = list->cols - 1;
    int **new_data = NULL;
    if (list->rows > 0) {
        new_data = malloc(list->rows * sizeof(int *));
        if (new_data == NULL) {
            return -2;
        }
    }
    for (int i = 0; i < list->rows; i++) {
        /* Possible weaknesses found:
         *  Condition 'new_cols>0' is always true [knownConditionTrueFalse]
         *  Condition 'new_cols>0' is always true
         */
        if (new_cols > 0) {
            new_data[i] = malloc(new_cols * sizeof(int));
            if (new_data[i] == NULL) {
                for (int j = 0; j < i; j++) {
                    free(new_data[j]);
                }
                free(new_data);
                return -2;
            }
            for (int j = 0, k = 0; j < list->cols; j++) {
                if (j != col) {
                    new_data[i][k++] = list->data[i][j];
                }
            }
        } else {
            new_data[i] = NULL;
        }
    }
    for (int i = 0; i < list->rows; i++) {
        free(list->data[i]);
    }
    free(list->data);
    list->data = new_data;
    list->cols = new_cols;
    return 0;
}

NestedList *create_nested_list(int rows, int cols) {
    if (rows < 0 || cols < 0) {
        return NULL;
    }
    NestedList *list = malloc(sizeof(NestedList));
    if (list == NULL) {
        return NULL;
    }
    list->rows = rows;
    list->cols = cols;
    list->data = NULL;
    if (rows > 0) {
        list->data = malloc(rows * sizeof(int *));
        if (list->data == NULL) {
            free(list);
            return NULL;
        }
        for (int i = 0; i < rows; i++) {
            if (cols > 0) {
                list->data[i] = malloc(cols * sizeof(int));
                if (list->data[i] == NULL) {
                    for (int j = 0; j < i; j++) {
                        free(list->data[j]);
                    }
                    free(list->data);
                    free(list);
                    return NULL;
                }
                for (int j = 0; j < cols; j++) {
                    list->data[i][j] = i * cols + j;
                }
            } else {
                list->data[i] = NULL;
            }
        }
    }
    return list;
}

void free_nested_list(NestedList *list) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < list->rows; i++) {
        free(list->data[i]);
    }
    free(list->data);
    free(list);
}

void print_nested_list(const NestedList *list) {
    if (list == NULL) {
        return;
    }
    for (int i = 0; i < list->rows; i++) {
        for (int j = 0; j < list->cols; j++) {
            printf("%d ", list->data[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    NestedList *list = create_nested_list(3, 4);
    if (list == NULL) {
        return 1;
    }
    print_nested_list(list);
    printf("\n");
    /* Possible weaknesses found:
     *  Calling function 'remove_column', 2nd argument '2' value is 2
     */
    int res = remove_column(list, 2);
    if (res != 0) {
        free_nested_list(list);
        return 1;
    }
    print_nested_list(list);
    free_nested_list(list);
    return 0;
}