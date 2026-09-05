#include <stdio.h>
#include <stdlib.h>

char*** create_3d_array(int depth, int rows, int cols)
{
    char ***array;
    int i, j, k;

    if (depth <= 0 || rows <= 0 || cols <= 0) {
        return NULL;
    }

    array = malloc(depth * sizeof(char **));
    if (array == NULL) {
        return NULL;
    }

    for (i = 0; i < depth; i++) {
        array[i] = malloc(rows * sizeof(char *));
        if (array[i] == NULL) {
            for (j = 0; j < i; j++) {
                for (k = 0; k < rows; k++) {
                    free(array[j][k]);
                }
                free(array[j]);
            }
            free(array);
            return NULL;
        }

        for (j = 0; j < rows; j++) {
            array[i][j] = malloc(cols * sizeof(char));
            if (array[i][j] == NULL) {
                for (k = 0; k < j; k++) {
                    free(array[i][k]);
                }
                free(array[i]);
                for (k = 0; k < i; k++) {
                    for (j = 0; j < rows; j++) {
                        free(array[k][j]);
                    }
                    free(array[k]);
                }
                free(array);
                return NULL;
            }

            for (k = 0; k < cols; k++) {
                array[i][j][k] = '*';
            }
        }
    }

    return array;
}

void free_3d_array(char ***array, int depth, int rows)
{
    int i, j;

    if (array == NULL) {
        return;
    }

    for (i = 0; i < depth; i++) {
        if (array[i] != NULL) {
            for (j = 0; j < rows; j++) {
                free(array[i][j]);
            }
            free(array[i]);
        }
    }
    free(array);
}

int main(void)
{
    int depth = 3;
    int rows = 4;
    int cols = 5;
    char ***array;
    int i, j, k;

    array = create_3d_array(depth, rows, cols);
    if (array == NULL) {
        fprintf(stderr, "Failed to create 3D array\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < depth; i++) {
        for (j = 0; j < rows; j++) {
            for (k = 0; k < cols; k++) {
                printf("%c ", array[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    free_3d_array(array, depth, rows);

    return EXIT_SUCCESS;
}