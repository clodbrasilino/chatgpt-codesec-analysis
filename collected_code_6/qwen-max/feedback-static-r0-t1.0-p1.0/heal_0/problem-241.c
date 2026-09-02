#include <stdio.h>
#include <stdlib.h>

void generate3DArray(char ***array, int x, int y, int z) {
    array[0] = malloc(x * sizeof(char*));
    if (array[0] == NULL) {
        fprintf(stderr, "Failed to allocate memory for 3D array\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < x; ++i) {
        array[0][i] = malloc(y * sizeof(char*));
        if (array[0][i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for 3D array\n");
            for (int j = 0; j < i; ++j) {
                free(array[0][j]);
            }
            free(array[0]);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < y; ++j) {
            array[0][i][j] = malloc(z * sizeof(char));
            if (array[0][i][j] == NULL) {
                fprintf(stderr, "Failed to allocate memory for 3D array\n");
                for (int k = 0; k < j; ++k) {
                    free(array[0][i][k]);
                }
                for (int l = 0; l < i; ++l) {
                    free(array[0][l]);
                }
                free(array[0]);
                exit(EXIT_FAILURE);
            }
            for (int k = 0; k < z; ++k) {
                array[0][i][j][k] = '*';
            }
        }
    }
}

void free3DArray(char ***array, int x, int y) {
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            free(array[0][i][j]);
        }
        free(array[0][i]);
    }
    free(array[0]);
}

int main() {
    char ***array;
    int x = 2, y = 3, z = 4;

    array = malloc(sizeof(char**));
    if (array == NULL) {
        fprintf(stderr, "Failed to allocate memory for 3D array pointer\n");
        return EXIT_FAILURE;
    }

    generate3DArray(array, x, y, z);

    // Print the 3D array
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                printf("%c ", array[0][i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    free3DArray(array, x, y);
    free(array);
    
    return 0;
}