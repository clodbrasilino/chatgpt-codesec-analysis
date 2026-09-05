#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** array, int rows, const int* cols, int index) {
    if (rows <= 0 || index < 0 || array == NULL || cols == NULL) {
        return NULL;
    }

    int* result = (int*)malloc(rows * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        if (array[i] == NULL || cols[i] <= index) {
            free(result);
            return NULL;
        }
        result[i] = array[i][index];
    }

    return result;
}

int main() {
    int row0[] = {10, 20, 30};
    int row1[] = {40, 50, 60};
    int row2[] = {70, 80, 90};
    
    int* array[] = {row0, row1, row2};
    const int cols[] = {3, 3, 3};
    int rows = 3;
    int index = 1;

    int* result = extract_elements(array, rows, cols, index);
    
    if (result != NULL) {
        for (int i = 0; i < rows; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("Extraction failed.\n");
    }

    return 0;
}