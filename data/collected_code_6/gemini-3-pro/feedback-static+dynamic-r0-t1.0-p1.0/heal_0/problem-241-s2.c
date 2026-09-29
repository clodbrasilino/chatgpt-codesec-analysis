#include <stdio.h>
#include <stdlib.h>

char ***generate_3d_array(size_t x, size_t y, size_t z) {
    if (x == 0 || y == 0 || z == 0) {
        return NULL;
    }

    char ***array = malloc(x * sizeof(char **));
    if (array == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < x; i++) {
        array[i] = malloc(y * sizeof(char *));
        if (array[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                for (size_t k = 0; k < y; k++) {
                    free(array[j][k]);
                }
                free(array[j]);
            }
            free(array);
            return NULL;
        }

        for (size_t j = 0; j < y; j++) {
            array[i][j] = malloc(z * sizeof(char));
            if (array[i][j] == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(array[i][k]);
                }
                free(array[i]);
                for (size_t k = 0; k < i; k++) {
                    for (size_t l = 0; l < y; l++) {
                        free(array[k][l]);
                    }
                    free(array[k]);
                }
                free(array);
                return NULL;
            }

            for (size_t k = 0; k < z; k++) {
                array[i][j][k] = '*';
            }
        }
    }

    return array;
}

void free_3d_array(char ***array, size_t x, size_t y) {
    if (array == NULL) {
        return;
    }

    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < y; j++) {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
}

int main(void) {
    size_t dim_x = 3;
    size_t dim_y = 4;
    size_t dim_z = 5;

    char ***my_array = generate_3d_array(dim_x, dim_y, dim_z);
    
    if (my_array == NULL) {
        fprintf(stderr, "Failed to allocate 3D array.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < dim_x; i++) {
        for (size_t j = 0; j < dim_y; j++) {
            for (size_t k = 0; k < dim_z; k++) {
                printf("%c ", my_array[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    free_3d_array(my_array, dim_x, dim_y);

    return EXIT_SUCCESS;
}