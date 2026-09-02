#include <stdio.h>
#include <stdlib.h>

int* extract_elements(int **list, int rows, int *cols, int index, int *result_size) {
    int *result = (int*)malloc(rows * sizeof(int));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < rows; i++) {
        if (index < cols[i]) {
            result[count++] = list[i][index];
        }
    }

    if (count == 0) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    int *final_result = (int*)realloc(result, count * sizeof(int));
    if (final_result == NULL) {
        free(result);
        *result_size = 0;
        return NULL;
    }

    *result_size = count;
    return final_result;
}

int main(void) {
    int row1[] = {1, 2, 3, 4};
    int row2[] = {5, 6};
    int row3[] = {7, 8, 9};
    int row4[] = {10};

    int *list[] = {row1, row2, row3, row4};
    int cols[] = {4, 2, 3, 1};
    int rows = 4;
    int index = 1;
    int result_size = 0;

    int *result = extract_elements(list, rows, cols, index, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    } else {
        printf("No elements extracted\n");
    }

    return 0;
}