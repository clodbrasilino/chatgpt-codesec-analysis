#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** array, int rows, const int* cols, int index) {
    if (array == NULL || rows <= 0 || cols == NULL) {
        return NULL;
    }

    int* result = (int*)malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        if (index < 0 || index >= cols[i] || array[i] == NULL) {
            result[i] = 0;
            continue;
        }
        result[i] = array[i][index];
    }

    return result;
}

int main() {
    int row0[] = {10, 20, 30};
    int row1[] = {40, 50};
    int row2[] = {60, 70, 80, 90};

    int rows = 3;
    /* Possible weaknesses found:
     *  Variable 'cols' can be declared as const array [constVariable]
     */
    int cols[] = {3, 2, 4};
    int** array = (int**)malloc(rows * sizeof(int*));
    if (array == NULL) {
        return 1;
    }

    array[0] = row0;
    array[1] = row1;
    array[2] = row2;

    int index = 1;
    int* result = extract_elements(array, rows, cols, index);

    if (result != NULL) {
        for (int i = 0; i < rows; i++) {
            printf("%d\n", result[i]);
        }
        free(result);
    }

    free(array);

    return 0;
}