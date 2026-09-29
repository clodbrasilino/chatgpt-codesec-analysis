#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 32

typedef struct {
    int rows;
    int cols;
    int **data;
} Matrix;

/* Possible weaknesses found:
 *  Parameter 'row1' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'row2' can be declared as pointer to const [constParameterPointer]
 */
static int rows_equal(int *row1, int *row2, int cols) {
    for (int i = 0; i < cols; i++) {
        if (row1[i] != row2[i])
            return 0;
    }
    return 1;
}

Matrix remove_similar_rows(Matrix *mat) {
    Matrix result;
    result.rows = 0;
    /* Possible weaknesses found:
     *  Either the condition 'mat==NULL' is redundant or there is possible null pointer dereference: mat. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    result.cols = mat->cols;
    result.data = NULL;

    /* Possible weaknesses found:
     *  Assuming that condition 'mat==NULL' is not redundant
     */
    if (mat == NULL || mat->rows <= 0 || mat->cols <= 0 || mat->data == NULL)
        return result;

    result.data = (int **)malloc(mat->rows * sizeof(int *));
    if (result.data == NULL)
        return result;

    for (int i = 0; i < mat->rows; i++) {
        int duplicate = 0;
        for (int j = 0; j < result.rows; j++) {
            if (rows_equal(mat->data[i], result.data[j], mat->cols)) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            result.data[result.rows] = (int *)malloc(mat->cols * sizeof(int));
            if (result.data[result.rows] == NULL) {
                for (int k = 0; k < result.rows; k++)
                    free(result.data[k]);
                free(result.data);
                result.data = NULL;
                result.rows = 0;
                return result;
            }
            memcpy(result.data[result.rows], mat->data[i], mat->cols * sizeof(int));
            result.rows++;
        }
    }

    int **temp = (int **)realloc(result.data, result.rows * sizeof(int *));
    if (temp != NULL || result.rows == 0) {
        result.data = temp;
    }

    return result;
}

void free_matrix(Matrix *mat) {
    if (mat == NULL || mat->data == NULL)
        return;
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    mat->data = NULL;
    mat->rows = 0;
}

int main(void) {
    Matrix mat;
    mat.rows = 5;
    mat.cols = 3;

    mat.data = (int **)malloc(mat.rows * sizeof(int *));
    if (mat.data == NULL)
        return 1;

    for (int i = 0; i < mat.rows; i++) {
        mat.data[i] = (int *)malloc(mat.cols * sizeof(int));
        if (mat.data[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(mat.data[j]);
            free(mat.data);
            return 1;
        }
    }

    int init_data[5][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {1, 2, 3},
        {7, 8, 9},
        {4, 5, 6}
    };

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            mat.data[i][j] = init_data[i][j];
        }
    }

    Matrix result = remove_similar_rows(&mat);

    printf("Original matrix:\n");
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%d ", mat.data[i][j]);
        }
        printf("\n");
    }

    printf("Matrix after removing similar rows:\n");
    if (result.data != NULL) {
        for (int i = 0; i < result.rows; i++) {
            for (int j = 0; j < result.cols; j++) {
                printf("%d ", result.data[i][j]);
            }
            printf("\n");
        }
    }

    free_matrix(&mat);
    free_matrix(&result);

    return 0;
}