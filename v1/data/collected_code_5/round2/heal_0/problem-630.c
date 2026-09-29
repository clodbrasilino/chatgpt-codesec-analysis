#include <stdio.h>

void getAdjacentCoordinates(int x, int y, int result[8][2]) {
    int direction[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (int i = 0; i < 8; i++) {
        result[i][0] = x + direction[i][0];
        result[i][1] = y + direction[i][1];
    }
}

int main() {
    int x = 2, y = 2;
    int result[8][2] = {0};

    getAdjacentCoordinates(x, y, result);

    for (int i = 0; i < 8; i++) {
        printf("(%d, %d)\n", result[i][0], result[i][1]);
    }

    return 0;
}