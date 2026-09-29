#include <stdio.h>

void generate3DArray(char arr[][3][3], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                arr[i][j][k] = '*';
            }
        }
    }
}

int main() {
    int size = 5; // Example size of the 3D array
    char arr[size][3][3];

    generate3DArray(arr, size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                printf("%c ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}