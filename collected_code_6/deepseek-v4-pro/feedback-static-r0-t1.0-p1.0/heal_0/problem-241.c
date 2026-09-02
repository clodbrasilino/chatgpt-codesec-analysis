#include <stdlib.h>

char ***generate_3d_star_array(int x, int y, int z) {
    char ***array = (char ***)malloc(x * sizeof(char **));
    if (array == NULL) {
        return NULL;
    }

    for (int i = 0; i < x; i++) {
        array[i] = (char **)malloc(y * sizeof(char *));
        if (array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < y; k++) {
                    free(array[j][k]);
                }
                free(array[j]);
            }
            free(array);
            return NULL;
        }

        for (int j = 0; j < y; j++) {
            array[i][j] = (char *)malloc(z * sizeof(char));
            if (array[i][j] == NULL) {
                for (int k = 0; k < j; k++) {
                    free(array[i][k]);
                }
                for (int k = i; k >= 0; k--) {
                    for (int l = 0; l < y; l++) {
                        free(array[k][l]);
                    }
                    free(array[k]);
                }
                free(array);
                return NULL;
            }

            for (int k = 0; k < z; k++) {
                array[i][j][k] = '*';
            }
        }
    }

    return array;
}

void free_3d_star_array(char ***array, int x, int y) {
    if (array == NULL) {
        return;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            free(array[i][j]);
        }
        free(array[i]);
    }
    free(array);
}

int main(void) {
    int x = 3, y = 4, z = 5;
    char ***array = generate_3d_star_array(x, y, z);

    if (array == NULL) {
        return 1;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                if (array[i][j][k] != '*') {
                    free_3d_star_array(array, x, y);
                    return 1;
                }
            }
        }
    }

    free_3d_star_array(array, x, y);
    return 0;
}