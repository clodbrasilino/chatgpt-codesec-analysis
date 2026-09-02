#include <stdio.h>
#include <stdlib.h>

int** extract_elements(int** list, int rows, int cols, int* indices, int indices_count, int** result_rows, int** result_cols) {
    if (list == NULL || indices == NULL || result_rows == NULL || result_cols == NULL) {
        return NULL;
    }
    
    if (rows <= 0 || cols <= 0 || indices_count <= 0) {
        return NULL;
    }
    
    int** result = (int**)malloc(indices_count * sizeof(int*));
    if (result == NULL) {
        return NULL;
    }
    
    *result_rows = (int*)malloc(indices_count * sizeof(int));
    if (*result_rows == NULL) {
        free(result);
        return NULL;
    }
    
    *result_cols = (int*)malloc(indices_count * sizeof(int));
    if (*result_cols == NULL) {
        free(*result_rows);
        free(result);
        return NULL;
    }
    
    for (int i = 0; i < indices_count; i++) {
        int index = indices[i];
        if (index < 0 || index >= rows * cols) {
            free(*result_cols);
            free(*result_rows);
            free(result);
            return NULL;
        }
        
        int row = index / cols;
        int col = index % cols;
        
        result[i] = (int*)malloc(sizeof(int));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(*result_cols);
            free(*result_rows);
            free(result);
            return NULL;
        }
        
        result[i][0] = list[row][col];
        (*result_rows)[i] = row;
        (*result_cols)[i] = col;
    }
    
    return result;
}

int main(void) {
    int rows = 3;
    int cols = 4;
    
    int** list = (int**)malloc(rows * sizeof(int*));
    if (list == NULL) {
        return 1;
    }
    
    for (int i = 0; i < rows; i++) {
        list[i] = (int*)malloc(cols * sizeof(int));
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            return 1;
        }
    }
    
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            list[i][j] = value++;
        }
    }
    
    int indices[] = {0, 5, 7, 11};
    int indices_count = 4;
    int* result_rows = NULL;
    int* result_cols = NULL;
    
    int** result = extract_elements(list, rows, cols, indices, indices_count, &result_rows, &result_cols);
    
    if (result != NULL) {
        for (int i = 0; i < indices_count; i++) {
            printf("Element at [%d][%d] = %d\n", result_rows[i], result_cols[i], result[i][0]);
        }
        
        for (int i = 0; i < indices_count; i++) {
            free(result[i]);
        }
        free(result);
        free(result_rows);
        free(result_cols);
    }
    
    for (int i = 0; i < rows; i++) {
        free(list[i]);
    }
    free(list);
    
    return 0;
}