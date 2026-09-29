#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int value1;
    int value2;
} Tuple;

int areTuplesSimilar(Tuple t1, Tuple t2) {
    return (t1.value1 == t2.value1 && t1.value2 == t2.value2);
}

int removeSimilarRows(Tuple** matrix, int rows) {
    if (matrix == NULL || *matrix == NULL || rows <= 0) {
        return 0;
    }

    int uniqueRows = 0;
    Tuple* arr = *matrix;

    for (int i = 0; i < rows; i++) {
        if (arr[i].id == -1) {
            continue;
        }

        int isSimilar = 0;
        for (int j = 0; j < uniqueRows; j++) {
            if (areTuplesSimilar(arr[i], arr[j])) {
                isSimilar = 1;
                break;
            }
        }

        if (!isSimilar) {
            arr[uniqueRows] = arr[i];
            uniqueRows++;
        }
    }

    if (uniqueRows > 0) {
        Tuple* resized = (Tuple*)realloc(arr, uniqueRows * sizeof(Tuple));
        if (resized != NULL) {
            *matrix = resized;
        }
    } else {
        free(arr);
        *matrix = NULL;
    }

    return uniqueRows;
}

int main(void) {
    int rows = 5;
    Tuple* matrix = (Tuple*)malloc(rows * sizeof(Tuple));
    
    if (matrix == NULL) {
        return 1;
    }

    matrix[0] = (Tuple){1, 10, 20};
    matrix[1] = (Tuple){2, 15, 25};
    matrix[2] = (Tuple){3, 10, 20};
    matrix[3] = (Tuple){4, 30, 40};
    matrix[4] = (Tuple){5, 15, 25};

    int newRows = removeSimilarRows(&matrix, rows);
    
    if (newRows < 0) {
        if (matrix != NULL) {
            free(matrix);
        }
        return 1;
    }

    for (int i = 0; i < newRows; i++) {
        printf("ID: %d, Value1: %d, Value2: %d\n", matrix[i].id, matrix[i].value1, matrix[i].value2);
    }

    if (matrix != NULL) {
        free(matrix);
    }
    
    return 0;
}