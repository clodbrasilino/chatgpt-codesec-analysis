#include <stdio.h>

void extractAdjacentCoordinates(int x, int y) {
    int adjacentCoordinates[8][2] = {
        {x - 1, y - 1}, {x - 1, y}, {x - 1, y + 1},
        {x, y - 1},                 {x, y + 1},
        {x + 1, y - 1}, {x + 1, y}, {x + 1, y + 1},
    };

    for (int i = 0; i < 8; i++) {
        int adjacentX = adjacentCoordinates[i][0];
        int adjacentY = adjacentCoordinates[i][1];
        printf("(%d, %d)\n", adjacentX, adjacentY);
    }
}

int main() {
    int x = 2; // Example x-coordinate
    int y = 3; // Example y-coordinate

    extractAdjacentCoordinates(x, y);

    return 0;
}