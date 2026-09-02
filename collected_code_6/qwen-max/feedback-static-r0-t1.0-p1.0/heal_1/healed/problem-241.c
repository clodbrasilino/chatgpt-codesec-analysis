#include <stdio.h>
#include <stdlib.h>

void generate3DArray(char ****array, int x, int y, int z) {
    *array = malloc(x * sizeof(char**));
    if (*array == NULL) {
        fprintf(stderr, "Failed to allocate memory for 3D array\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < x; ++i) {
        (*array)[i] = malloc(y * sizeof(char*));
        if ((*array)[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for 3D array\n");
            for (int j = 0; j < i; ++j) {
                free((*array)[j]);
            }
            free(*array);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < y; ++j) {
            (*array)[i][j] = malloc(z * sizeof(char));
            if ((*array)[i][j] == NULL) {
                fprintf(stderr, "Failed to allocate memory for 3D array\n");
                for (int k = 0; k < j; ++k) {
                    free((*array)[i][k]);
                }
                for (int l = 0; l < i; ++l) {
                    free((*array)[l]);
                }
                free(*array);
                exit(EXIT_FAILURE);
            }
            for (int k = 0; k < z; ++k) {
                (*array)[i][j][k] = '*';
            }
        }
    }
}

void free3DArray(char ***array, int x, int y) {
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
}

int main() {
    char ****array;
    int x = 2, y = 3, z = 4;

    array = malloc(sizeof(char***));
    if (array == NULL) {
        fprintf(stderr, "Failed to allocate memory for 3D array pointer\n");
        return EXIT_FAILURE;
    }

    generate3DArray(array, x, y, z);

    // Print the 3D array
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                printf("%c ", (*array)[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    free3DArray(*array, x, y);
    free(array);
    
    return 0;
}