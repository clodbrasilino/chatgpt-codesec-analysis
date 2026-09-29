#include <stdio.h>
#include <stdlib.h>

int count_integral_coordinates(int x1, int y1, int x2, int y2) {
    int width = abs(x2 - x1) + 1;
    int height = abs(y2 - y1) + 1;
    return width * height;
}

int main() {
    int x1, y1, x2, y2;

    printf("Enter the coordinates of the bottom-left corner (x1, y1): ");
    scanf("%d %d", &x1, &y1);
    printf("Enter the coordinates of the top-right corner (x2, y2): ");
    scanf("%d %d", &x2, &y2);

    int count = count_integral_coordinates(x1, y1, x2, y2);
    printf("Number of integral coordinates: %d\n", count);

    return 0;
}