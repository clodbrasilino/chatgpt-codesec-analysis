#include <stdio.h>
#include <stdlib.h>

char*** create3dArray(int x,int y,int z) {
    
    char ***arr = (char ***)malloc(x * sizeof(char **));
    
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < x; i++) {
        arr[i] = (char **)malloc(y * sizeof(char *));
        if (arr[i] == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        for(int j = 0; j < y; j++) {
            arr[i][j] = (char *)malloc(z * sizeof(char));
            if (arr[i][j] == NULL) {
                printf("Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }

            for(int k = 0; k < z; k++) {
                arr[i][j][k] = '*';
            }
        }
    }
    
    return arr;
}

void delete3dArray(char*** arr, int x, int y) {
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);
}

int main() {
    const int dimensions = 3;
    char ***array = create3dArray(dimensions, dimensions, dimensions);

    for(int i = 0; i < dimensions; i++){
        for(int j = 0; j < dimensions; j++){
            for(int k = 0; k < dimensions; k++){
                printf("%c ", array[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    delete3dArray(array, dimensions, dimensions);

    return 0;
}