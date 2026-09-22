#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int** list, int rows, int cols, int extract_index, int* result_size) {
    if (list == NULL || rows <= 0 || cols <= 0 || extract_index < 0 || extract_index >= cols || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    int* extracted = (int*)malloc(rows * sizeof(int));
    if (extracted == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        if (list[i] == NULL) {
            free(extracted);
            *result_size = 0;
            return NULL;
        }
        extracted[i] = list[i][extract_index];
    }

    *result_size = rows;
    return extracted;
}

int main(void) {
    int rows = 3;
    int cols = 4;
    int extract_index = 2;

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
        for (int j = 0; j < cols; j++) {
            list[i][j] = i * cols + j;
        }
    }

    int result_size = 0;
    int* extracted = extract_elements(list, rows, cols, extract_index, &result_size);

    if (extracted != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", extracted[i]);
        }
        printf("\n");
        free(extracted);
    }

    for (int i = 0; i < rows; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}