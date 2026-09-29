#include <stdio.h>
#include <stdlib.h>

char*** generate_3d_array(int x, int y, int z) {
    if (x <= 0 || y <= 0 || z <= 0) {
        return NULL;
    }

    char*** arr = (char***)malloc(x * sizeof(char**));
    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < x; i++) {
        arr[i] = (char**)malloc(y * sizeof(char*));
        if (arr[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return NULL;
        }

        for (int j = 0; j < y; j++) {
            arr[i][j] = (char*)malloc(z * sizeof(char));
            if (arr[i][j] == NULL) {
                for (int k = 0; k < j; k++) {
                    free(arr[i][k]);
                }
                free(arr[i]);
                for (int j2 = 0; j2 < i; j2++) {
                    for (int k2 = 0; k2 < y; k2++) {
                        free(arr[j2][k2]);
                    }
                    free(arr[j2]);
                }
                free(arr);
                return NULL;
            }

            for (int k = 0; k < z; k++) {
                arr[i][j][k] = '*';
            }
        }
    }

    return arr;
}

void free_3d_array(char*** arr, int x, int y) {
    if (arr == NULL) {
        return;
    }

    for (int i = 0; i < x; i++) {
        if (arr[i] != NULL) {
            for (int j = 0; j < y; j++) {
                free(arr[i][j]);
            }
            free(arr[i]);
        }
    }
    free(arr);
}

int main(void) {
    int x = 2;
    int y = 3;
    int z = 4;

    char*** my_array = generate_3d_array(x, y, z);
    if (my_array == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < z; k++) {
                printf("%c ", my_array[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    free_3d_array(my_array, x, y);

    return EXIT_SUCCESS;
}