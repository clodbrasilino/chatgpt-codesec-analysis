#include <stdio.h>

#define X 3
#define Y 3
#define Z 3

void generate3DArray(char arr[X][Y][Z]) {
    for(int i = 0; i < X; i++) {
        for(int j = 0; j < Y; j++) {
            for(int k = 0; k < Z; k++) {
                arr[i][j][k] = '*';
            }
        }
    }
}

void print3DArray(char arr[X][Y][Z]) {
    for(int i = 0; i < X; i++) {
        for(int j = 0; j < Y; j++) {
            for(int k = 0; k < Z; k++) {
                printf("%c ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main() {
    char arr[X][Y][Z];
    generate3DArray(arr);
    print3DArray(arr);
    return 0;
}