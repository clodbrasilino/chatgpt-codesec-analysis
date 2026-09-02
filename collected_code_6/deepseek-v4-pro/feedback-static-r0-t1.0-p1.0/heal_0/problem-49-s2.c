#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** list, int rows, int index, int* result_size) {
    if (list == NULL || rows <= 0 || index < 0 || result_size == NULL) {
        *result_size = 0;
        return NULL;
    }

    int* result = (int*)malloc(rows * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        if (list[i] == NULL) {
            free(result);
            *result_size = 0;
            return NULL;
        }
        result[i] = list[i][index];
    }

    *result_size = rows;
    return result;
}

int main(void) {
    int row1[] = {1, 2, 3};
    int row2[] = {4, 5, 6};
    int row3[] = {7, 8, 9};
    
    int* list[] = {row1, row2, row3};
    int result_size = 0;
    
    int* extracted = extract_elements(list, 3, 0, &result_size);
    
    if (extracted != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    }
    
    return 0;
}