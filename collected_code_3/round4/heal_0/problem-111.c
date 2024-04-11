#include <stdio.h>
#include <stdbool.h>

#define ROW 4
#define COL 5

bool isCommon(int mat[ROW][COL], int x) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (mat[i][j] == x)
                return true;
        }
    }
    return false;
}

void findCommon(int mat[ROW][COL]) {
    for (int i = 0; i < COL; i++) {
        if (isCommon(mat, mat[0][i]))
            printf("%d ", mat[0][i]);
    }
}

int main() {
    int mat[ROW][COL] = {
        {1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6},
        {3, 4, 5, 6, 7},
        {4, 5, 6, 7, 8}
    };

    findCommon(mat);

    return 0;
}